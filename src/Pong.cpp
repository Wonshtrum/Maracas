#include "Application.h"


#define INPUTS Maracas::InputsStates

struct rgb {
	float r;
	float g;
	float b;
};

rgb hsvToRgb(float h, float s, float v) {
	int hi = ((int)(h/60))%6;
	float f = h/60 - hi;
	float l = v*(1-s);
	float m = v*(1-f*s);
	float n = v*(1-(1-f)*s);
	rgb res;
	switch(hi) {
		case 0:
			res = { v, n, l };
			break;
		case 1:
			res = { m, v, l };
			break;
		case 2:
			res = { l, v, n };
			break;
		case 3:
			res = { l, m, v };
			break;
		case 4:
			res = { n, l, v };
			break;
		case 5:
			res = { v, l, m };
			break;
		default:
			break;
	}
	return res;
}

class PongLayer: public Maracas::Layer {
	public:
		PongLayer(const char* debugName, Maracas::GraphicsContext* context): Layer(debugName), m_context(context) {
			float vertices[] = {
				-1, -1, 1.0f, 0.0f, 0.0f,
				 1, -1, 0.0f, 1.0f, 0.0f,
				 1,  1, 0.0f, 0.0f, 1.0f,
				-1,  1, 1.0f, 1.0f, 0.0f,
				 0,  0, 0.0f, 0.0f, 0.0f
			};
			unsigned int indices[] {
				0, 1, 2,
				2, 3, 0,
			};

			Maracas::BufferElement elements[] = {{Maracas::ShaderData::Float2, "a_position"}, {Maracas::ShaderData::Float3, "a_color"}};
			Maracas::BufferLayout layout(elements, 2);
			
			m_vao = m_context->createVertexArray();
			m_vbo = m_context->createVertexBuffer(vertices, sizeof(vertices));
			m_ibo = m_context->createIndexBuffer(indices, sizeof(vertices));

			m_vbo->setLayout(&layout);
			m_vao->addVertexBuffer(m_vbo);
			m_vao->setIndexBuffer(m_ibo);

			m_vao->unbind();
			m_ibo->unbind();
			m_vbo->unbind();

			vertices[0] = 0;

			m_shader = new Maracas::Shader(R"(
				#version 330 core
				layout(location = 0) in vec4 a_position;
				out vec4 v_position;
				uniform mat4 u_transform;
				void main() {
					v_position = a_position;
					gl_Position = u_transform * a_position;
				})", R"(
				#version 330 core
				in vec4 v_position;
				uniform float u_x;
				uniform float u_y;
				uniform vec3 u_color;
				layout(location = 0) out vec4 color;
				void main() {
					float d = 6*distance(vec4(u_x,u_y,0.0,1.0),v_position)+1;
					color = vec4(u_color,0.05+1/(d*d*d*d));
				})");

			m_shaderPad = new Maracas::Shader(R"(
				#version 330 core
				layout(location = 0) in vec4 a_position;
				out vec4 v_position;
				uniform mat4 u_transform;
				void main() {
					v_position = a_position;
					gl_Position = u_transform * a_position;
				})", R"(
				#version 330 core
				in vec4 v_position;
				uniform float u_x;
				uniform float u_y;
				uniform vec3 u_color;
				layout(location = 0) out vec4 color;
				void main() {
					color = vec4(u_color, 0.5);
				})");
		}

		~PongLayer () {
			delete m_shader;
			delete m_shaderPad;
			delete m_vao;
			delete m_vbo;
			delete m_ibo;
			MRC_ERROR(m_debugName, " cleared");
		}

		virtual void onEvent(Maracas::Event& event) override {
			//MRC_CORE_DEBUG(event.toString());
		}

		virtual void onUpdate(float deltaTime) override {
			if (INPUTS::getKey(MRC_KEY_W) || INPUTS::getKey(MRC_KEY_RIGHT)) {
				m_pad1 += m_vpad * deltaTime;
				if (m_pad1 + m_height > 1) {
					m_pad1 = 1 - m_height;
				}
			}
			if (INPUTS::getKey(MRC_KEY_S) || INPUTS::getKey(MRC_KEY_LEFT)) {
				m_pad1 -= m_vpad * deltaTime;
				if (m_pad1 - m_height < -1) {
					m_pad1 = -1 + m_height;
				}
			}
			if (INPUTS::getKey(MRC_KEY_UP) || INPUTS::getKey(MRC_KEY_D)) {
				m_pad2 += m_vpad * deltaTime;
				if (m_pad2 + m_height > 1) {
					m_pad2 = 1 - m_height;
				}
			}
			if (INPUTS::getKey(MRC_KEY_DOWN) || INPUTS::getKey(MRC_KEY_A)) {
				m_pad2 -= m_vpad * deltaTime;
				if (m_pad2 - m_height < -1) {
					m_pad2 = -1 + m_height;
				}
			}
			m_hue += m_vhue * deltaTime;
			if (m_hue > 360) {
				m_hue -= 360;
			}
			rgb color = hsvToRgb(m_hue, 1, 1);
			m_shader->bind();
			int locX = glGetUniformLocation(m_shader->getProgram(), "u_x");
			int locY = glGetUniformLocation(m_shader->getProgram(), "u_y");
			int locC = glGetUniformLocation(m_shader->getProgram(), "u_color");
			glUniform1f(locX, m_px);
			glUniform1f(locY, m_py);
			glUniform3f(locC, color.r, color.g, color.b);
			m_shaderPad->bind();
			locC = glGetUniformLocation(m_shaderPad->getProgram(), "u_color");
			glUniform3f(locC, color.r, color.g, color.b);
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.8f));
			glm::mat4 s = scale;
			for (int i = 0 ; i<50 ; i++) {
				m_context->drawTriangles(m_vao, m_shader, s);
				s *= scale;
			}
			glm::mat4 transPad1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f+m_width, m_pad1, 0.0f));
			glm::mat4 transPad2 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f-m_width, m_pad2, 0.0f));
			glm::mat4 scalePad = glm::scale(glm::mat4(1.0f), glm::vec3(m_width, m_height, 0.0f));
			m_context->drawTriangles(m_vao, m_shaderPad, scale*transPad1*scalePad);
			m_context->drawTriangles(m_vao, m_shaderPad, scale*transPad2*scalePad);
			m_px += m_vx * deltaTime;
			m_py += m_vy * deltaTime;
			
			if (m_py > 1) {
				m_py = 2 - m_py;
				m_vy *= -1;
			} else if (m_py < -1) {
				m_py = -2 - m_py;
				m_vy *= -1;
			}
			if (m_px > 1) {
				if (m_pad1-m_height < m_py && m_pad1+m_height > m_py) {
					m_px = 2 - m_px;
					m_vx *= -1;
				} else {
					m_px = 0;
					m_py = 0;
				}
			} else if (m_px < -1) {
				if (m_pad2-m_height < m_py && m_pad2+m_height > m_py) {
					m_px = -2 - m_px;
					m_vx *= -1;
				} else {
					m_px = 0;
					m_py = 0;
				}
			}
		}
	protected:
		Maracas::GraphicsContext* m_context;
		Maracas::VertexArray* m_vao;
		Maracas::VertexBuffer* m_vbo;
		Maracas::IndexBuffer* m_ibo;
		Maracas::Shader* m_shader;
		Maracas::Shader* m_shaderPad;
		float m_height = 0.3f;
		float m_width = 0.02f;
		float m_hue = 0.0f;
		float m_vhue = 60.0f;
		float m_px = 0.0f;
		float m_py = 0.0f;
		float m_vx = 0.81f;
		float m_vy = 1.26f;
		float m_pad1 = 0.0f;
		float m_pad2 = 0.0f;
		float m_vpad = 2.0f;
};

class Pong: public Maracas::Application {
	public:
		Pong() {
			MRC_INFO("Application started");
			m_window = Maracas::Window::createWindow("Pong",700,700);
			m_window->setEventCallback(BIND(Pong::onEvent));
			m_context = m_window->getContext();
			glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
			m_layerStack.insertBegin(new PongLayer("GraphicLayer", m_context));
		}
		~Pong() {
			delete m_window;
			MRC_INFO("Application stoped");
		}
		virtual void onUpdate(float deltaTime) override {
			m_window->pollEvents();
			m_context->clearColor(0.0,0.07,0.1,1);
			m_layerStack.onUpdate(deltaTime);
			m_context->swapBuffers();
		}
	private:
		Maracas::Window* m_window;
		Maracas::GraphicsContext* m_context;
};

Maracas::Application* Maracas::createApplication() {
	return new Pong();
}

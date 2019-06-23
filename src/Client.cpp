#include "Application.h"


#define INPUTS Maracas::InputsStates
class MyApp : public Maracas::Application {
	public:
		MyApp() {
			MRC_INFO("Application started");
			m_window = Maracas::Window::createWindow("Client Application",700,700);
			m_window->setEventCallback(BIND(MyApp::onEvent));
			m_context = m_window->getContext();

			float d = 0.75f;
			float vertices[] = {
				-d, -d, 1.0f, 0.0f, 0.0f,
				 d, -d, 0.0f, 1.0f, 0.0f,
				 d,  d, 0.0f, 0.0f, 1.0f,
				-d,  d, 1.0f, 1.0f, 0.0f,
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

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_shader = new Maracas::Shader(R"(
				#version 330 core
				layout(location = 0) in vec4 a_position;
				out vec4 v_position;
				void main() {
					v_position = a_position;
					gl_Position = a_position;
				})", R"(
				#version 330 core
				in vec4 v_position;
				uniform float u_x;
				uniform float u_y;
				layout(location = 0) out vec4 color;
				void main() {
					float d = 1*distance(vec4(u_x,u_y,0.0,1.0),v_position)+1;
					color = vec4(1,0.0,0.0,1/(d*d*d*d));
				})");
		}

		~MyApp() {
			delete m_window;
			delete m_shader;
			delete m_vao;
			delete m_vbo;
			delete m_ibo;
			MRC_INFO("Application stoped");
		}

		void onUpdate() override {
			m_shader->bind();
			int locX = glGetUniformLocation(m_shader->getProgram(), "u_x");
			int locY = glGetUniformLocation(m_shader->getProgram(), "u_y");
			float H = 350.0f;
			float W = 350.0f;
			m_window->pollEvents();
			glUniform1f(locX, (INPUTS::getCursorX()-W)/W);
			glUniform1f(locY, (H-INPUTS::getCursorY())/H);
			m_vao->bind();
			m_context->clearColor(0.0,0.07,0.1,1);
			m_context->drawTriangles(m_vao);
			m_context->swapBuffers();
		}
	private:
		Maracas::Window* m_window;
		Maracas::GraphicsContext* m_context;
		Maracas::VertexArray* m_vao;
		Maracas::VertexBuffer* m_vbo;
		Maracas::IndexBuffer* m_ibo;
		Maracas::Shader* m_shader;
};

Maracas::Application* Maracas::createApplication() {
	return new MyApp();
}


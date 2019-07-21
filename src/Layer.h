#ifndef MRC_LAYER_H
#define MRC_LAYER_H
#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"
#include "Event.h"

/* =========================================== *
 * Layer specific macros
 * =========================================== */
//ENDHEAD
namespace Maracas {
	class LayerStack;
	class Layer {
		public:
			friend LayerStack;
			Layer(const char* debugName): m_debugName(debugName) {}
			virtual ~Layer() {}
		protected:
			virtual void onAttach() {};
			virtual void onDettach() {};
			virtual void onUpdate(float deltaTime) {};
			virtual void onEvent(Event& event) {};
			const char* m_debugName;
	};

	class LayerStack: public LinkedList<Layer> {
		public:
			LayerStack() {}
			~LayerStack() {}
			virtual void insertAfter(Layer* layer) override;
			virtual void insertBefore(Layer* layer) override;
			virtual void insertBegin(Layer* layer) override;
			virtual void insertEnd(Layer* layer) override;
			virtual Layer* popBegin() override;
			virtual Layer* popEnd() override;
			virtual Layer* pop() override;
			void onUpdate(float deltaTime);
			void onEvent(Event& event);
	};
}

#endif

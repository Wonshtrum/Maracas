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
			virtual void onAttach() = 0;
			virtual void onDettach() = 0;
			virtual void onUpdate() = 0;
			virtual void onEvent(Event& event) = 0;
			const char* m_debugName;
	};

	class LayerStack: public LinkedList<Layer> {
		public:
			LayerStack(Layer* layer): LinkedList(layer) { layer->onAttach(); }
			~LayerStack() {}
			virtual void insertAfter(Layer* layer) override;
			virtual void insertBefore(Layer* layer) override;
			virtual void insertBegin(Layer* layer) override;
			virtual void insertEnd(Layer* layer) override;
			virtual Layer* popBegin() override;
			virtual Layer* popEnd() override;
			virtual Layer* pop() override;
			void onUpdate();
			void onEvent(Event& event);
	};
}

#endif

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
			Layer() {}
			virtual ~Layer() {}
		protected:
			virtual void onAttach() = 0;
			virtual void onDettach() = 0;
			virtual void onUpdate() = 0;
			virtual void onEvent(Event& event) = 0;
	};

	class LayerStack: public LinkedList<Layer> {
		public:
			LayerStack(Layer* layer): LinkedList(layer) {}
			~LayerStack() {}
			void insertAfter(Layer* layer);
			void insertBefore(Layer* layer);
			void insertBegin(Layer* layer);
			void insertEnd(Layer* layer);
			Layer* popBegin();
			Layer* popEnd();
			Layer* pop();
			void onUpdate();
			void onEvent(Event& event);
	};
}

#endif

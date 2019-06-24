#ifndef MRC_LAYER_H
#define MRC_LAYER_H
#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"

/* =========================================== *
 * Layer specific macros
 * =========================================== */
//ENDHEAD
namespace Maracas {
	class Layer {
		Layer() {}
		virtual ~Layer() {}
		virtual void onAttach() = 0;
		virtual void onDettach() = 0;
		virtual void onUpdate() = 0;
	};

	class LayerStack {
		public:
			LayerStack() {}
			~LayerStack() {}
			void pushLayer(Layer* layer) {}
			void popLayer(Layer* layer) {}
			int getCount() { return m_count; }
		private:
			LinkedList<Layer>* layers;
			int m_count = 0;
	};
}

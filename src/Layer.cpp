#include "Layer.h"

namespace Maracas {
	void LayerStack::insertAfter(Layer* layer) {
		layer->onAttach();
		LinkedList::insertAfter(layer);
	}
	void LayerStack::insertBefore(Layer* layer) {
		layer->onAttach();
		LinkedList::insertBefore(layer);
	}
	void LayerStack::insertBegin(Layer* layer) {
		layer->onAttach();
		LinkedList::insertBegin(layer);
	}
	void LayerStack::insertEnd(Layer* layer) {
		layer->onAttach();
		LinkedList::insertEnd(layer);
	}
	Layer* LayerStack::popBegin() {
		tail->element->onDettach();
		return LinkedList::popBegin();
	}
	Layer* LayerStack::popEnd() {
		head->element->onDettach();
		return LinkedList::popEnd();
	}
	Layer* LayerStack::pop() {
		current->element->onDettach();
		return LinkedList::pop();
	}
	void LayerStack::onUpdate() {
		listElement<Layer>* layer = tail;
		while (layer)  {
			layer->element->onUpdate();
			layer = layer->next;
		}
	}
	void LayerStack::onEvent(Event& event) {
		listElement<Layer>* layer = head;
		while (layer) {
			layer->element->onEvent(event);
			if (event.m_handled) {
				break;
			}
			layer = layer->previous;
		}
	}
}

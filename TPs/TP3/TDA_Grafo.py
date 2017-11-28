#Lucia Pardo 99999 - Federico del Mazo 100029
#TP3 - TDA GRAFO
#Corrige Gonzalo

import random
from collections import deque
from collections import Counter
CANT_LABEL_PROPAGATION = 50

class Grafo:
	def __init__(self):
		self.dic_adyacencias = {}	
		
	def __repr__(self):
		return str(self.dic_adyacencias)
	
	def __len__(self):
		return len(self.dic_adyacencias)
	
	def __iter__(self):
		return iter(self.dic_adyacencias.keys())

	def agregar_vertice(self, v):
		self.dic_adyacencias[v] = []
	
	def borrar_vertice(self, v):
		if self.pertenece(v):
			for v2 in self:
				self.borrar_arista(v, v2)
			return self.dic_adyacencias.pop(v)
		
	def agregar_arista(self, v1, v2):
		if not self.pertenece(v1):
			self.agregar_vertice(v1)
		if not self.pertenece(v2):
			self.agregar_vertice(v2)
		if not v1 in self.dic_adyacencias[v2]:
			self.dic_adyacencias[v2].append(v1)
		if not v2 in self.dic_adyacencias[v1]:
			self.dic_adyacencias[v1].append(v2)

	def borrar_arista(self,v1,v2):
		if self.son_adyacentes(v1,v2):
			self.dic_adyacencias[v1].remove(v2)
			self.dic_adyacencias[v2].remove(v1)

	def son_adyacentes(self, v1, v2):
		return v1 in self.dic_adyacencias[v2]
	
	def adyacentes(self, v):
		if not self.pertenece(v):
			return None
		return self.dic_adyacencias[v]
	
	def vertices(self):
		return self.dic_adyacencias.keys()
	
	def aristas(self):
		aristas = []
		for v in self:
			for w in self.dic_adyacencias[v]:
				tupla = (v, w)
				aristas.append(tupla)
	
	def pertenece(self, v):
		return v in self.dic_adyacencias
				
	def random_walk(self, origen, pasos):
		lista = []
		siguiente = origen
		for i in range(pasos):
			siguiente = random.choice(self.dic_adyacencias[siguiente])
			lista.append(siguiente)
		return lista
	
	def cant_aristas(self):
		cant = 0
		for v in self:
			cant+=len(self.adyacentes(v))
		return int(cant/2)
	
	def bfs(self, origen):
		origen = str(origen)
		visitados = {}
		dic_bfs = {}
		orden = {}
		cola = deque(origen)
		visitados[origen] = True
		orden[origen] = 0
		while len(cola)>0:
			v=cola.popleft()
			for w in self.adyacentes(v):
				if w not in visitados:
					orden[w]=orden[v]+1
					visitados[w]=True
					cola.append(w)
					if orden[w] in dic_bfs:
						dic_bfs[orden[w]].append(w)
					else:
						dic_bfs[orden[w]] = [w]
		return dic_bfs
	
	def label_propagation(self):
		labels = {}
		for v,i in zip(self,range(len(self))):
			labels[v] = i
		for v,i in zip(self,range(CANT_LABEL_PROPAGATION)):
			c = Counter(self.adyacentes(v))
			labels[v] = (c.most_common())[0][0]
		return labels



class Grafo:
	"""
	Modelo de un grafo no pesado, no dirigido, con nombres en las aristas, y que los vertices puedan ser conectados por dos aristas distintas
	Se compone de dos diccionarios.
		El de vertices, que contiene como clave al vertice y como valor un set de los nombres de todas sus aristas
		El de aristas, que contiene como clave al nombre de la arista y como valor un set de los vertices que la contengan
	"""
	def __init__(self):
		self.dic_vertices = {}
		self.dic_aristas = {}

	def __repr__(self):
		"""La representacion formal es el diccionario de vertices"""
		return str(self.dic_vertices)

	def __str__(self):
		"""La representacion informal es el la cantidad de aristas y vertices"""
		return "Grafo de {} vertices y {} aristas".format(len(self.vertices()), len(self.aristas()))

	def __len__(self):
		"""La longitud del grafo en si es la cantidad de vertices"""
		return len(self.dic_vertices)

	def __contains__(self, vertice):
		"""Permite uso de 'vertice in grafo' y 'vertice not in grafo'"""
		return vertice in self.dic_vertices

	def __getitem__(self, vertice):
		"""Permite el hacer grafo[vertice] que devuelve su lista de aristas"""
		return self.dic_vertices[vertice]

	def __setitem__(self, vertice, nombre_aristas):
		"""Permite hacer grafo[vertice] = [arista1,arista2]"""
		self.dic_vertices[vertice] = nombre_aristas

	def __iter__(self):
		"""Permite hacer for vertice in grafo"""
		return iter(self.dic_vertices.keys())

	def agregar_vertice(self, v):
		"""De no estar presente, agrega un vertice, sin aristas al grafo"""
		if v not in self: self[v] = set()
		
	def borrar_vertice(self, v):
		"""Borra al vertice de todas las aristas del grafo, y luego del grafo en si"""
		for arista in self[v]:
			for adyacente in self.dic_aristas[arista]:
				if adyacente == v: self.dic_aristas[arista].remove(adyacente)
		self.dic_vertices.pop(v)

	def agregar_arista(self, vertice, arista):
		"""Agrega tanto a la arista al vertice como al vertice a la arista"""
		self.agregar_vertice(vertice)
		self[vertice].add(arista)
		if arista not in self.dic_aristas: self.dic_aristas[arista] = set()
		self.dic_aristas[arista].add(vertice)

	def borrar_arista(self, vertice, arista):
		"""Borra a la arista del vertice recibido, y si la arista queda sin vertices la borra del grafo"""
		self[vertice].remove(arista)
		if len(self[vertice]) == 0: self.dic_vertices.pop(vertice)

	def vertices(self):
		"""Devuelve el set de vertices"""
		return set(self.dic_vertices.keys())

	def aristas(self):
		"""Devuelve el set de aristas"""
		return set(self.dic_aristas.keys())

	def adyacentes(self, v):
		"""Devuelve todos los vertices adyacentes al vertice recibido. Para esto itera sobre todas las aristas del v y agrega a sus vertices"""
		adyacentes_totales = set()
		for arista in self[v]:
			adyacentes_totales.update(self.dic_aristas[arista])
		return [adyacente for adyacente in adyacentes_totales if adyacente != v]

	def son_adyacentes(self, v1, v2):
		"""Verifica que v1 este en los adyacentes de v2 y viceversa"""
		return v1 in self.adyacentes(v2) and v2 in self.adyacentes(v1)

	def aristas_que_unen(self, v1, v2):
		"""Devuelve un conjunto de todas las aristas que unen a v1 con v2"""
		aristas_v1 = self[v1]
		aristas_v2 = self[v2]
		return { arista for arista in aristas_v1 if arista in aristas_v2 }

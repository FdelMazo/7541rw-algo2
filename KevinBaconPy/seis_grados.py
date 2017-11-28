from collections import deque
from grafo import Grafo
import random
from collections import Counter

CANT_RANDOM_WALKS = 1000
PASOS_RANDOM_WALKS = 5
BFS = {}

def _minimo_camino(grafo, dic_bfs, final , corte):
	"""
	Funcion auxiliar usada por camino. Con un diccionario de bfs partiendo desde el origen recrea el camino desde el origen hasta el final
	PRE: Recibe el grafo, el diccionario de distancias del origen, el actor de llegada, y la cantidad de pasos entre origen y final
	POST: Devuelve una lista ordenada para llegar desde el origen hasta el final
	"""
	camino = []
	actual = final
	for i in range(corte-1, -1, -1):
		adyacentes_actual = grafo.adyacentes(actual)
		for actor in adyacentes_actual:
			if actor in dic_bfs[i]:
				camino.insert(0, (actor, actual, grafo.aristas_que_unen(actual, actor).pop()))
				actual = actor
				break
	return camino

def camino(grafo, origen, final):
	"""
	Devuelve el camino entre un actor de origen y uno de llegada
	PRE: Recibe el grafo, un actor de origen y un actor de llegada
	POST: Devuelve una lista ordenada para llegar desde el origen hasta el final
	"""
	if origen not in grafo or final not in grafo: return []
	dic_bfs = bfs(grafo, origen) if origen not in BFS else BFS[origen]
	corte = None
	for orden in dic_bfs:
		if final in dic_bfs[orden]:
			corte = orden
			break
	if corte == None: return False
	camino = _minimo_camino(grafo, dic_bfs, final, corte)
	return camino

def actores_a_distancia(grafo, origen, n):
	"""
	PRE: Recibe el grafo, el actor de origen y el n deseado
	POST: Devuelve el set de actores a n pasos del recibido
	"""
	dic_bfs = bfs(grafo, origen) if origen not in BFS else BFS[origen]
	if not dic_bfs: return False
	return dic_bfs.get(n)

def popularidad(grafo, actor):
	"""
	Calcula la popularidad del actor recibido
	PRE: Recibe el grafo y un actor de origen
	POST: Devuelve un entero que simboliza la popularidad: Todos los adyacentes de los adyacentes del actor, multiplicado por su cantidad de peliculas
	"""
	if actor not in grafo: return False
	dic_distancia2 = actores_a_distancia(grafo,actor,2)
	popularidad = len(dic_distancia2) * len(grafo[actor])
	return popularidad

def similares(grafo,origen, n):
	"""
	Calcula los n actores mas similares al actor de origen y los devuelve en una lista ordenada
	PRE: Recibe el grafo, el actor de origen, y el n deseado
	POST: Devuelve una lista de los n actores no adyacentes al de origen que mas aparezcan en los random walks realizados. La lista no contiene al actor de origen
	"""
	if origen not in grafo: return False
	total_random_walks = []
	for i in range(CANT_RANDOM_WALKS):
		rw = random_walk(grafo, origen, PASOS_RANDOM_WALKS)
		rw_filtrado = [a for a in rw if a not in grafo.adyacentes(origen)]
		rw_filtrado = [a for a in rw if a != origen]
		total_random_walks.extend(rw_filtrado)
	return [a[0] for a in Counter(total_random_walks).most_common(n)]

####################################################################
def grafo_crear(nombre_archivo):
	"""
	Genera un grafo a partir de un archivo.
	PRE: Recibe el nombre de un archivo separado por comas que contenga de lineas:
		actor,pelicula,pelicula,pelicula
		esto equivale a: vertice,arista,arista,arista
	POST: Devuelve un grafo creado a partir de estos datos.
	"""
	grafo = Grafo()
	with open(nombre_archivo, encoding="utf8") as file:
		for linea in file:
			vertice, aristas = linea.split(',')[0], linea.split(',')[1:]
			grafo.agregar_vertice(vertice)
			for arista in aristas:
				grafo.agregar_arista(vertice, arista.rstrip())
	return grafo

def bfs(grafo, origen):
	"""
	Genera un diccionario de todos los actores agrupados por la cantidad de pasos desde el origen.
	PRE: Recibe el grafo, el actor de origen, y si se lo desea un actor de llegada para cortar la ejecucion
	POST: Devuelve un diccionario de clave n y valores un set de los vertices a n pasos del origen.
	"""
	if origen not in grafo: return False
	dic_bfs, orden, visitados = {}, {}, {}
	dic_bfs[0], orden[origen], visitados[origen] = [origen], 0, True
	cola = deque()
	cola.append(origen)
	while len(cola) > 0:
		v = cola.popleft()
		for w in grafo.adyacentes(v):
			if w not in visitados:
				visitados[w] = True
				orden[w] = orden[v] + 1
				cola.append(w)
				if orden[w] in dic_bfs:
					dic_bfs[orden[w]].add(w)
				else:
					dic_bfs[orden[w]] = set([w])
	global BFS
	BFS[origen] = dic_bfs
	return dic_bfs

def random_walk(grafo, origen, pasos):
	"""
	Hace un random walk de largo _pasos_ desde el origen
	PRE: Recibe el grafo, el actor de origen y la cantidad de pasos a dar
	POST: Devuelve una lista ordenada del camino hecho al azar
	"""
	actual = origen
	recorrido = []
	for i in range(pasos):
		recorrido.append(actual)
		actual = random.choice(grafo.adyacentes(actual))
	return recorrido
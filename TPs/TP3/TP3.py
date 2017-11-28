#Lucia Pardo 99999 - Federico del Mazo 100029
#TP3 - PROGRAMA
#Corrige Gonzalo

import sys
import random
from TDA_Grafo import Grafo
CANT_RANDOM_WALKS = 5000
PROF_RANDOM_WALKS = 5
CANT_MINIMA_COMUNIDAD = 4
CANT_MAXIMA_COMUNIDAD = 2000

def generar_grafo(n_archivo):
	archivo = open(n_archivo)
	grafo = Grafo()
	for linea in archivo:
		if linea[0] == "#":
			continue
		vertice1, vertice2 = linea.rstrip('\n').split("\t")
		grafo.agregar_arista(vertice1, vertice2)
	return grafo

def funciones_random_walk(grafo, id, n, funcion):
	id = str(id)
	similares = {}
	for j in range(CANT_RANDOM_WALKS):
		if funcion=="centralidad":
			id = random.choice(list(grafo.vertices()))
		camino = grafo.random_walk(id, PROF_RANDOM_WALKS)
		similar = camino[PROF_RANDOM_WALKS-1]
		if funcion=="recomendar" and similar in grafo.adyacentes(id):
			continue
		if similar in similares:
			similares[similar]+=1
		else:
			similares[similar] = 1
	tuplas = sorted(similares.items(), key=lambda x: x[1], reverse=True)
	lista = []
	for i in range(n):
		if i>=len(tuplas):
			break
		lista.append(tuplas[i][0])
	return lista

def camino(grafo,partida,llegada):
	partida=str(partida)
	llegada=str(llegada)
	dic_bfs = grafo.bfs(partida)
	cant_pasos = 0
	camino = []
	for pasos, lista in dic_bfs.items():
		if llegada in lista:
			cant_pasos = pasos
	for lista, i in zip(dic_bfs.values(), range(cant_pasos)):
		camino.append(lista[0])
	if cant_pasos != 0:
		camino.insert(0, partida)
		camino.append(llegada)
	return camino
				
def recomendar(grafo, id, n):
	return funciones_random_walk(grafo, id, n, "recomendar")

def similares(grafo, id, n):
	return funciones_random_walk(grafo, id, n, "similares")

def centralidad(grafo, n):
	return funciones_random_walk(grafo, id, n, "centralidad")

def comunidades(grafo):
	comunidades_dict = {}
	comunidades_lst = []
	labels = grafo.label_propagation()
	for v,label in labels.items():
		if label in comunidades_dict:
			comunidades_dict[label].append(v)
		else:
			comunidades_dict[label] = [v]
	for label,lista in comunidades_dict.items():
		if len(lista) > CANT_MINIMA_COMUNIDAD and len(lista) < CANT_MAXIMA_COMUNIDAD:
			dict = {len(lista):lista}
			comunidades_lst.append(dict)
	return comunidades_lst
		
def distancias(grafo,id):
	dic_bfs = grafo.bfs(id)
	distancia = {}
	for pasos, lista in dic_bfs.items():
		distancia[pasos] = len(lista)
	return distancia

def estadisticas(grafo):
	cant_aristas = grafo.cant_aristas()
	cant_vertices = len(grafo)
	grado_promedio = cant_aristas / cant_vertices
	denso = (2 * cant_aristas)/(cant_vertices**2)
	print("Cantidad de vertices: {}".format(cant_vertices))
	print("Cantidad de aristas: {}".format(cant_aristas))
	print("Grado promedio de salida/entrada de cada vertice: {:.2}".format(grado_promedio))	
	print("Denso: {}".format(int(denso)))

def crear_menu():
	menu = {}
	menu['similares'] = similares
	menu['recomendar'] = recomendar
	menu['camino'] = camino
	menu['centralidad'] = centralidad
	menu['distancias'] = distancias
	menu['estadisticas'] = estadisticas
	menu['comunidades'] = comunidades
	return menu

def main():
	menu = crear_menu()
	n_archivo = sys.argv[1]
	grafo = generar_grafo(n_archivo)
	print("Grafo generado exitosamente.")
	while True:
		try:
			linea_stdin = input()
		except EOFError:
			break
		split = linea_stdin.split()
		comando = split[0]
		parametros = [int(i) for i in split[1:]]
		print(menu[comando](grafo, *parametros))
		
main()

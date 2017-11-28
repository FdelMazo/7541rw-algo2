from sys import argv
import seis_grados
import time

KB = "Bacon Kevin"

def main():
	"""
	Programa que ejecuta diversas operaciones sobre Kevin Bacon y otros actores.
	Primero genera el grafo del archivo recibido por CLA, y luego da un input de comandos.
	Los comandos deben ser el nombre de la funcion, y los parametros entre comillas, sin especificar al grafo. Por ej:
		popularidad_contra_KB "Watts Naomi"
	Cuando el comando sea una linea vacia, se corta la ejecucion
	Siempre debe ser ejecutado pasandole un archivo csv como CLA y puede ser llamado tanto con un archivo de texto que lista los comandos, como normalmente y esperando al inputo del usuario:
		`cat comandos.txt | python3 kevinbacon.py actors.csv`
		`python3 kevinbacon.py actors.csv`
	"""
	start = time.clock()
	grafo = seis_grados.grafo_crear(argv[1])
	end = time.clock()
	print("Grafo de {} cargado exitosamente en {:.4f} segundos.".format(argv[1], end-start))
	menu = menu_funciones()
	print("Comandos disponibles:" )
	for k in menu.keys():
		print('\t* '+k)
	linea_input = input("\nEscriba un comando: ").split("'")
	while linea_input:
		start = time.clock()
		comando = linea_input[0].strip()
		parametros = [i for i in linea_input[1:] if i.strip()]
		print(comando, parametros)
		if not comando: break
		menu[comando](grafo, *parametros)
		end = time.clock()
		print("En {:.4f} segundos.".format( end-start))
		linea_input = input("\nEscriba un comando: ").split("'")
	print("Fin de la ejecucion")
	
def menu_funciones():
	menu = {}
	menu['camino_hasta_KB'] = camino_hasta_KB
	menu['bacon_number'] = bacon_number
	menu['bacon_number_mayor_a_6'] = bacon_number_mayor_a_6
	menu['KBN_promedio'] = KBN_promedio
	menu['bacon_number_infinito'] = bacon_number_infinito
	menu['similares_a_KB'] = similares_a_KB
	menu['popularidad_contra_KB'] = popularidad_contra_KB
	menu['cantidad_peliculas'] = cantidad_peliculas
	menu['cantidad_actores'] = cantidad_actores
	return menu
	
####################################################################
def camino_hasta_KB(grafo,actor):
	"""
	Imprime el camino más corto con el cual se llega desde cualquier actor hasta Kevin Bacon. 
	De no haber camino posible se debe imprimir un mensaje acorde (por ejemplo: “No hay conexion entre KB y el actor”) y 
	de no existir el actor ingresado se debe imprimir un mensaje acorde.
	"""
	if actor not in grafo: 
		print("{} no existe".format(actor))
		return
	camino_a_KB = seis_grados.camino(grafo, KB, actor)
	if not camino_a_KB:
		print("No hay conexion entre KB y {}".format(actor))
		return
	largo = len(camino_a_KB)
	for i in reversed(range(largo)):
		print ("'{}' actuo con '{}' en '{}'".format(camino_a_KB[i][1],camino_a_KB[i][0],camino_a_KB[i][2]))

def bacon_number(grafo,actor):
	"""
	Imprime el Kevin Bacon Number del actor recibido. Para representar un KBN infinito (no hay conexión entre KB y el actor) el KBN esperado es -1, 
	y de no existir el actor ingresado se debe imprimir un mensaje acorde. Tener en cuenta que el KBN de Kevin Bacon es 0.
	"""
	if actor not in grafo: 
		print("{} no existe".format(actor))
		return
	camino = seis_grados.camino(grafo,actor, KB)
	if not camino and actor != KB:
		print("'{}' tiene un Kevin Bacon Number igual a -1".format(actor))
		return
	k = len(camino)
	print("'{}' tiene un Kevin Bacon Number igual a {}".format(actor, k))


def bacon_number_mayor_a_6(grafo):
	"""
	Imprime la cantidad de actores (¿existirán?) a una distancia mayor a 6 pasos de Kevin Bacon. 
	De no existir actores a más pasos que 6, se imprime un mensaje acorde. 
	En este numero no influyen la cantidad de actores con un KBN infinito.
	"""
	bfs = seis_grados.bfs(grafo,KB)
	if len(bfs)<=7:
		print("Kevin Bacon no tiene actores a una distancia mayor a 6!")
		return
	print("Los  actores con un KBN mayor a 6 son:")
	total = 0
	for k,personas in bfs.items():
		if k > 6 :
			total += len(personas)
			print("Con KBN igual a {}: {} actores".format(k,len(personas)))

def bacon_number_infinito(grafo):
	"""
	Imprime la cantidad de actores (¿existirán?) con un KBN infinito. De no haber, se debe imprimir un mensaje acorde.
	"""
	conocidos = set()
	for i in seis_grados.bfs(grafo,KB).values():
		conocidos.update(i)
	a = len(grafo.vertices() - conocidos)
	if a == 0:
		print("No existen actores desconectados a KB")
		return
	print("Los actores con un Bacon Number infinito son {}".format(a))
			
def KBN_promedio(grafo):
	"""
	Imprime el Kevin Bacon Number promedio. 
	En este numero no influyen la cantidad de actores con un KBN infinito, pero si lo hace el KBN de Kevin Bacon.
	"""
	bfs = seis_grados.bfs(grafo,KB)
	KBN, alcanzados = 0, 0
	for k,personas in bfs.items():
		alcanzados += len(personas)
		KBN += k * len(personas)
	promedio = KBN / alcanzados
	print("El Kevin Bacon Number promedio es {}".format(promedio))
			
def similares_a_KB(grafo, n):
	"""
	Imprime una lista de los n actores más similares a Kevin Bacon, ordenados de mayor similitud a menor.
	"""
	s = seis_grados.similares(grafo, KB, int(n))
	print("Los {} actores más similares a KB son: {}".format(n,s))

def popularidad_contra_KB(grafo, actor):
	"""
	Usando su popularidad como base, imprime en porcentaje cuán popular es el actor en comparación a KB. 
	De no existir el actor ingresado, se debe imprimir un mensaje acorde y devolver None. 
	Tener en cuenta que Kevin Bacon es un 100% de lo popular que es Kevin Bacon
	"""
	if actor not in grafo: 
		print("{} no existe".format(actor))
		return
	pop_KB = seis_grados.popularidad(grafo,KB)
	pop_actor = seis_grados.popularidad(grafo,actor)
	final = pop_actor*100/pop_KB
	print("'{}' es un {:.2f}% de lo popular que es Kevin Bacon".format(actor,final))

def cantidad_peliculas(grafo):
	"""
	Imprime y devuelve la cantidad de películas en el dataset
	"""
	p = len(grafo.aristas())
	print("El dataset contiene {} películas".format(p))

def cantidad_actores(grafo):
	"""
	Imprime y devuelve la cantidad de películas en el dataset
	"""
	a = len(grafo.vertices())
	print("El dataset contiene {} actores".format(a))
	

####################################################################
if __name__ == "__main__":
	main()	


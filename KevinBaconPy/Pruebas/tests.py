import sys
import unittest
import time
from seis_grados import *
from timeout import timeout

NOMBRE_GRAFO = "test.csv"

class SeisGradosTests(unittest.TestCase):

	@classmethod
	def setUpClass(test):
		start = time.clock()
		test.grafo = grafo_crear(NOMBRE_GRAFO)
		end = time.clock()
		print("Grafo {} cargado exitosamente en {:.4f} segundos".format(NOMBRE_GRAFO, end - start))
	
	def setUp(self):
		self._started_at = time.time()

	def tearDown(self):
		elapsed = time.time() - self._started_at
		sys.stderr.write('en {:.4f}s '.format(elapsed))

	@timeout(2, "El test tardó demasiado!")
	def test_camino(self):
		self.assertEqual(len(camino(self.grafo, 'Bacon Kevin', 'Penn Sean')), 1)
		self.assertEqual(len(camino(self.grafo, 'Bacon Kevin', 'Watts Naomi')), 2)
		self.assertEqual(len(camino(self.grafo, 'Bacon Kevin', 'Fishburne Laurence')), 1)
		self.assertEqual(len(camino(self.grafo, 'Bacon Kevin', 'Reeves Keanu')), 2)

	def test_camino_negativo(self):
		self.assertFalse(camino(self.grafo, 'Bacon Kevin', 'Cosme Fulanito'), "De no estar presente el actor se debe devolver False")
		self.assertFalse(camino(self.grafo, 'Cosme Fulanito', 'Bacon Kevin'), "De no estar presente el actor se debe devolver False")
		
	def test_camino_trivial(self):
		self.assertFalse(camino(self.grafo, 'Bacon Kevin', 'Bacon Kevin'), "De calcular el camino entre el mismo actor se debe devolver una lista vacia")

	@timeout(2, "El test tardó demasiado!")
	def test_actores_a_distancia(self):
		self.assertEqual(len(actores_a_distancia(self.grafo, 'Bacon Kevin', 1)), 9)
		self.assertEqual(len(actores_a_distancia(self.grafo, 'Bacon Kevin', 2)), 22)
		self.assertEqual(len(actores_a_distancia(self.grafo, 'Bacon Kevin', 3)), 52)
		self.assertEqual(len(actores_a_distancia(self.grafo, 'Bacon Kevin', 4)), 69)
		self.assertEqual(len(actores_a_distancia(self.grafo, 'Bacon Kevin', 5)), 40)
		self.assertEqual(len(actores_a_distancia(self.grafo, 'Bacon Kevin', 6)), 18)

	def test_actores_a_distancia_negativo(self):
		self.assertFalse(actores_a_distancia(self.grafo, 'Cosme Fulanito', 0), "De no estar presente el actor se debe devolver False")
	
	def test_actores_a_distancia_trivial(self):
		self.assertEqual(len(actores_a_distancia(self.grafo, 'Bacon Kevin', 0)), 1, "Todo actor esta a una distancia 0 de si mismo")
			
	def test_popularidad(self):
		self.assertEqual(popularidad(self.grafo, 'Bacon Kevin'), 1452)
		self.assertEqual(popularidad(self.grafo, 'Penn Sean'), 1760)
		self.assertEqual(popularidad(self.grafo, 'Watts Naomi'), 1652)
		self.assertEqual(popularidad(self.grafo, 'Fishburne Laurence'), 4047)
		self.assertEqual(popularidad(self.grafo, 'Reeves Keanu'), 1512)
		
	def test_popularidad_negativo(self):
		self.assertFalse(popularidad(self.grafo, 'Cosme Fulanito'), "De no estar presente el actor se debe devolver False")
		
	def test_similares(self):
		self.assertTrue('Bacon Kevin' not in similares(self.grafo, 'Bacon Kevin',1), "El mismo actor no debe estar en la lista de similares")
		self.assertTrue(len(similares(self.grafo, 'Bacon Kevin',2)), 2)
	
	def test_similares_trivial(self):
		self.assertFalse(similares(self.grafo, 'Bacon Kevin',0), "De pedir los 0 similares se debe devolver una lista vacia")
	
	def test_similares_negativo(self):
		self.assertFalse(similares(self.grafo, 'Cosme Fulanito',0), "De no estar presente el actor se debe devolver False")


if __name__ == "__main__":
	unittest.main(verbosity=2, failfast=True)

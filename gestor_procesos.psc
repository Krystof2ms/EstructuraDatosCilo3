// ============================================================
//   GESTOR DE PROCESOS - PSeInt (sin Registro, con funciones)
//   Estructuras: Lista ordenada, Cola, Pila, Validadores
// ============================================================


// ============================================================
//  VALIDADORES
// ============================================================

Funcion resultado <- ValidarRango(msg, minVal, maxVal)
	Definir valor Como Entero
	Repetir
		Escribir msg Sin Saltar
		Leer valor
		Si valor < minVal O valor > maxVal Entonces
			Escribir "Valor fuera de rango. Ingrese entre (", minVal, " - ", maxVal, ")"
		FinSi
	Hasta Que valor >= minVal Y valor <= maxVal
	resultado <- valor
FinFuncion

Funcion resultado <- ValidarPositivo(msg, errorMsg)
	Definir valor Como Entero
	Repetir
		Escribir msg Sin Saltar
		Leer valor
		Si valor < 0 Entonces
			Escribir errorMsg
		FinSi
	Hasta Que valor >= 0
	resultado <- valor
FinFuncion

Funcion resultado <- ValidarNombre(msg)
	Definir nombre Como Caracter
	Repetir
		Escribir msg Sin Saltar
		Leer nombre
		Si nombre = "" Entonces
			Escribir "El nombre no puede estar vacio."
		FinSi
	Hasta Que nombre <> ""
	resultado <- nombre
FinFuncion

Funcion resultado <- ValidarConfirmacion(msg)
	Definir resp Como Caracter
	Repetir
		Escribir msg, " (s/n): " Sin Saltar
		Leer resp
		Si resp <> "s" Y resp <> "n" Y resp <> "S" Y resp <> "N" Entonces
			Escribir "Respuesta invalida. Ingrese s o n"
		FinSi
	Hasta Que resp = "s" O resp = "n" O resp = "S" O resp = "N"
	resultado <- (resp = "s" O resp = "S")
FinFuncion

// ============================================================
//  LISTA DE PROCESOS
// ============================================================

// Muestra un proceso por su indice
SubProceso MostrarProceso(id, nombre, prioridad)
	Escribir "ID: ", id, "  Nombre: ", nombre, "  Prioridad: ", prioridad
FinSubProceso

// Devuelve 1 si el ID existe en la lista, 0 si no
Funcion encontrado <- BuscarProceso(listId, listNombre, listPrioridad, listTam, idBuscado)
	Definir i, encontrado Como Entero
	encontrado <- 0
	Para i <- 1 Hasta listTam Hacer
		Si listId[i] = idBuscado Entonces
			MostrarProceso(listId[i], listNombre[i], listPrioridad[i])
			encontrado <- 1
		FinSi
	FinPara
FinFuncion

// Inserta un proceso manteniendo orden por prioridad (menor = mas prioritario)
SubProceso InsertarEnOrden(listId Por Referencia, listNombre Por Referencia, listPrioridad Por Referencia, listTam Por Referencia, nuevoId, nuevoNombre, nuevaPrioridad)
	Definir i, j Como Entero
	listTam <- listTam + 1
	i <- listTam
	// Desplazar elementos con prioridad mayor hacia la derecha
	Mientras i > 1 Y listPrioridad[i-1] > nuevaPrioridad Hacer
		listId[i]        <- listId[i-1]
		listNombre[i]    <- listNombre[i-1]
		listPrioridad[i] <- listPrioridad[i-1]
		i <- i - 1
	FinMientras
	listId[i]        <- nuevoId
	listNombre[i]    <- nuevoNombre
	listPrioridad[i] <- nuevaPrioridad
FinSubProceso

// Elimina un proceso por ID; devuelve 1 si lo encontro
Funcion exito <- EliminarProceso(listId Por Referencia, listNombre Por Referencia, listPrioridad Por Referencia, listTam Por Referencia, idEliminar)
	Definir i, pos, exito Como Entero
	pos <- 0
	Para i <- 1 Hasta listTam Hacer
		Si listId[i] = idEliminar Entonces
			pos <- i
		FinSi
	FinPara
	Si pos = 0 Entonces
		exito <- 0
	SiNo
		Para i <- pos Hasta listTam - 1 Hacer
			listId[i]        <- listId[i+1]
			listNombre[i]    <- listNombre[i+1]
			listPrioridad[i] <- listPrioridad[i+1]
		FinPara
		listTam <- listTam - 1
		exito <- 1
	FinSi
FinFuncion

// Modifica un proceso existente por ID
SubProceso ModificarProceso(listId Por Referencia, listNombre Por Referencia, listPrioridad Por Referencia, listTam Por Referencia, idModificar, nuevoId, nuevoNombre, nuevaPrioridad)
	Definir i, pos, exito Como Entero
	exito <- 0
	pos <- 0
	Para i <- 1 Hasta listTam Hacer
		Si listId[i] = idModificar Entonces
			pos <- i
		FinSi
	FinPara
	Si pos = 0 Entonces
		Escribir "Proceso no encontrado."
	SiNo
		// Eliminar el viejo y reinsertar en orden con los nuevos datos
		exito <- EliminarProceso(listId, listNombre, listPrioridad, listTam, idModificar)
		InsertarEnOrden(listId, listNombre, listPrioridad, listTam, nuevoId, nuevoNombre, nuevaPrioridad)
		Escribir "Proceso modificado exitosamente."
	FinSi
FinSubProceso

// Valida que el ID no exista ya en la lista
Funcion idNuevo <- ValidarIdUnico(listId, listTam)
	Definir id, existe, k, idNuevo Como Entero
	
	Repetir
		id <- ValidarPositivo("Ingrese el ID del proceso: ", "El ID debe ser un numero positivo.")
		
		existe <- 0
		
		Si listTam > 0 Entonces
			Para k <- 1 Hasta listTam Hacer
				Si listId[k] = id Entonces
					existe <- 1
				FinSi
			FinPara
		FinSi
		
		Si existe = 1 Entonces
			Escribir "El ID ya existe. Ingrese un ID unico."
		FinSi
		
	Hasta Que existe = 0
	
	idNuevo <- id
FinFuncion

// Menu de procesos se llama como subrutina desde el algoritmo principal
SubProceso LlamarMenuProcesos(listId Por Referencia, listNombre Por Referencia, listPrioridad Por Referencia, listTam Por Referencia)
	Definir op, id, nuevoId, nuevaPrioridad, exito, k Como Entero
	Definir nuevoNombre Como Caracter
	Repetir
		Escribir ""
		Escribir "====== Menu de Procesos ======"
		Escribir "1. Registrar proceso"
		Escribir "2. Buscar proceso por ID"
		Escribir "3. Modificar proceso por ID"
		Escribir "4. Eliminar proceso por ID"
		Escribir "5. Mostrar todos los procesos"
		Escribir "6. Volver"
		op <- ValidarRango("Seleccione una opcion: ", 1, 6)
		Segun op Hacer
			1:	// Registrar
				id           <- ValidarIdUnico(listId, listTam)
				nuevoNombre  <- ValidarNombre("Ingrese el nombre del proceso: ")
				nuevaPrioridad <- ValidarRango("Ingrese la prioridad (1-10): ", 1, 10)
				InsertarEnOrden(listId, listNombre, listPrioridad, listTam, id, nuevoNombre, nuevaPrioridad)
				Escribir "Proceso registrado exitosamente."
			2:	// Buscar
				id <- ValidarPositivo("Ingrese el ID a buscar: ", "El ID debe ser positivo.")
				Si BuscarProceso(listId, listNombre, listPrioridad, listTam, id) = 0 Entonces
					Escribir "Proceso no encontrado."
				FinSi
			3:	// Modificar
				id           <- ValidarPositivo("Ingrese el ID a modificar: ", "El ID debe ser positivo.")
				nuevoId      <- ValidarPositivo("Ingrese el nuevo ID: ", "El ID debe ser positivo.")
				nuevoNombre  <- ValidarNombre("Ingrese el nuevo nombre: ")
				nuevaPrioridad <- ValidarRango("Ingrese la nueva prioridad (1-10): ", 1, 10)
				ModificarProceso(listId, listNombre, listPrioridad, listTam, id, nuevoId, nuevoNombre, nuevaPrioridad)
			4:	// Eliminar
				id <- ValidarPositivo("Ingrese el ID a eliminar: ", "El ID debe ser positivo.")
				exito <- EliminarProceso(listId, listNombre, listPrioridad, listTam, id)
				Si exito = 1 Entonces
					Escribir "Proceso eliminado exitosamente."
				SiNo
					Escribir "No se encontro un proceso con ese ID."
				FinSi
			5:	// Mostrar
				Si listTam = 0 Entonces
					Escribir "No hay procesos registrados."
				SiNo
					Para k <- 1 Hasta listTam Hacer
						MostrarProceso(listId[k], listNombre[k], listPrioridad[k])
					FinPara
				FinSi
			6:	Escribir "Volviendo..."
		FinSegun
	Hasta Que op = 6
FinSubProceso

// ============================================================
//  COLA DE LISTOS (FIFO circular sobre arreglo)
// ============================================================

Funcion Encolar(colaId Por Referencia, colaInicio Por Referencia, colaFin Por Referencia, colaTam Por Referencia, idProceso)
	Si colaTam >= 100 Entonces
		Escribir "La cola esta llena."
	SiNo
		colaFin <- colaFin + 1
		Si colaFin > 100 Entonces
			colaFin <- 1
		FinSi
		colaId[colaFin] <- idProceso
		colaTam <- colaTam + 1
	FinSi
FinFuncion

Funcion exito <- Desencolar(colaId Por Referencia, colaInicio Por Referencia, colaFin Por Referencia, colaTam Por Referencia, idSalida Por Referencia)
	Si colaTam = 0 Entonces
		exito <- 0
	SiNo
		idSalida <- colaId[colaInicio]
		colaInicio <- colaInicio + 1
		Si colaInicio > 100 Entonces
			colaInicio <- 1
		FinSi
		colaTam <- colaTam - 1
		exito <- 1
	FinSi
FinFuncion

Funcion MostrarCola(colaId, colaInicio, colaTam)
	Definir i, pos Como Entero
	Si colaTam = 0 Entonces
		Escribir "La cola esta vacia."
	SiNo
		Escribir "Procesos en cola: " Sin Saltar
		Para i <- 0 Hasta colaTam - 1 Hacer
			pos <- colaInicio + i
			Si pos > 100 Entonces
				pos <- pos - 100
			FinSi
			Escribir colaId[pos], " " Sin Saltar
		FinPara
		Escribir ""
	FinSi
FinFuncion

SubProceso LlamarMenuPlanificador(listId, listNombre, listPrioridad, listTam, colaId Por Referencia, colaInicio Por Referencia, colaFin Por Referencia, colaTam Por Referencia)
	Definir op, id, idSalida, exito Como Entero
	Repetir
		Escribir ""
		Escribir "====== Menu del Planificador ======"
		Escribir "1. Encolar proceso"
		Escribir "2. Desencolar proceso"
		Escribir "3. Mostrar procesos en cola"
		Escribir "4. Ejecutar todos los procesos"
		Escribir "5. Volver"
		op <- ValidarRango("Seleccione una opcion: ", 1, 5)
		Segun op Hacer
			1:
				Si listTam = 0 Entonces
					Escribir "No hay procesos registrados para encolar."
				SiNo
					id <- ValidarPositivo("Ingrese el ID del proceso a encolar: ", "El ID debe ser positivo.")
					Si BuscarProceso(listId, listNombre, listPrioridad, listTam, id) = 0 Entonces
						Escribir "Ese ID no existe en la lista de procesos."
					SiNo
						Encolar(colaId, colaInicio, colaFin, colaTam, id)
						Escribir "Proceso ", id, " encolado exitosamente."
					FinSi
				FinSi
			2:
				exito <- Desencolar(colaId, colaInicio, colaFin, colaTam, idSalida)
				Si exito = 1 Entonces
					Escribir "Proceso desencolado con ID: ", idSalida
				SiNo
					Escribir "La cola esta vacia."
				FinSi
			3:
				MostrarCola(colaId, colaInicio, colaTam)
			4:
				Si colaTam = 0 Entonces
					Escribir "No hay procesos en cola para ejecutar."
				SiNo
					Repetir
						exito <- Desencolar(colaId, colaInicio, colaFin, colaTam, idSalida)
						Si exito = 1 Entonces
							Escribir "Ejecutando proceso ID ", idSalida, ":"
							exito <- BuscarProceso(listId, listNombre, listPrioridad, listTam, idSalida)
						FinSi
					Hasta Que exito = 0
				FinSi
			5:
				Escribir "Volviendo..."
		FinSegun
	Hasta Que op = 5
FinSubProceso

// ============================================================
//  PILA DE MEMORIA (LIFO)
// ============================================================

Funcion Apilar(pilaId Por Referencia, pilaTope Por Referencia, idProceso)
	Si pilaTope >= 100 Entonces
		Escribir "La pila esta llena."
	SiNo
		pilaTope <- pilaTope + 1
		pilaId[pilaTope] <- idProceso
	FinSi
FinFuncion

Funcion exito <- Desapilar(pilaId Por Referencia, pilaTope Por Referencia, idSalida Por Referencia)
	Si pilaTope = 0 Entonces
		exito <- 0
	SiNo
		idSalida <- pilaId[pilaTope]
		pilaTope <- pilaTope - 1
		exito <- 1
	FinSi
FinFuncion

Funcion MostrarPila(pilaId, pilaTope)
	Definir i Como Entero
	Si pilaTope = 0 Entonces
		Escribir "No hay procesos con memoria asignada."
	SiNo
		Para i <- pilaTope Hasta 1 Con Paso -1 Hacer
			Escribir "ID del proceso con memoria en la pila: ", pilaId[i]
		FinPara
	FinSi
FinFuncion

SubProceso LlamarMenuMemoria(listId, listTam, pilaId Por Referencia, pilaTope Por Referencia)
	Definir op, id, idSalida, exito, k, existe Como Entero
	Repetir
		Escribir ""
		Escribir "====== Menu de la Memoria ======"
		Escribir "1. Asignar memoria a proceso"
		Escribir "2. Liberar memoria de proceso"
		Escribir "3. Mostrar procesos con memoria asignada"
		Escribir "4. Vaciar memoria"
		Escribir "5. Volver"
		op <- ValidarRango("Seleccione una opcion: ", 1, 5)
		Segun op Hacer
			1:
				id <- ValidarPositivo("Ingrese el ID del proceso: ", "El ID debe ser positivo.")
				// Verificar que el proceso exista en la lista
				existe <- 0
				Para k <- 1 Hasta listTam Hacer
					Si listId[k] = id Entonces
						existe <- 1
					FinSi
				FinPara
				Si existe = 0 Entonces
					Escribir "Ese ID no existe en la lista de procesos."
				SiNo
					Apilar(pilaId, pilaTope, id)
					Escribir "Memoria asignada al proceso con ID ", id, "."
				FinSi
			2:
				exito <- Desapilar(pilaId, pilaTope, idSalida)
				Si exito = 1 Entonces
					Escribir "Memoria liberada del proceso con ID ", idSalida, "."
				SiNo
					Escribir "No hay procesos con memoria para liberar."
				FinSi
			3:
				MostrarPila(pilaId, pilaTope)
			4:
				pilaTope <- 0
				Escribir "Memoria vaciada."
			5:
				Escribir "Volviendo..."
		FinSegun
	Hasta Que op = 5
FinSubProceso

Algoritmo GestorProcesos
	// Variables globales simuladas con arreglos paralelos

	// Lista de procesos (ordenada por prioridad)
	Definir listId, listPrioridad, listTam Como Entero
	Definir listNombre Como Caracter
	Dimension listId[100], listPrioridad[100]
	Dimension listNombre[100]
	listTam <- 0

	// Cola de listos (FIFO) guarda IDs
	Definir colaId  Como Entero
	Dimension colaId[100]
	Definir colaInicio, colaFin, colaTam Como Entero
	colaInicio <- 1
	colaFin    <- 0
	colaTam    <- 0

	// Pila de memoria (LIFO) guarda IDs
	Definir pilaId Como Entero
	Dimension pilaId[100]
	Definir pilaTope Como Entero
	pilaTope <- 0

	// Menu principal 
	Definir op Como Entero
	Repetir
		Escribir ""
		Escribir "====== Menu Principal ======"
		Escribir "1. Gestion de Procesos"
		Escribir "2. Planificador de Procesos"
		Escribir "3. Gestion de Memoria"
		Escribir "4. Salir"
		op <- ValidarRango("Seleccione una opcion: ", 1, 4)
		Segun op Hacer
			1: 
				LlamarMenuProcesos(listId, listNombre, listPrioridad, listTam)
			2: 
				LlamarMenuPlanificador(listId, listNombre, listPrioridad, listTam, colaId, colaInicio, colaFin, colaTam)
			3: 
				LlamarMenuMemoria(listId, listTam, pilaId, pilaTope)
			4: Escribir "Saliendo del programa."
		FinSegun
	Hasta Que op = 4

FinAlgoritmo


# Tarea 2 - 2024-2

Nicolás Hörmann
23662492

# Ejecución:

Para tener los ejecutables pegasus y secretfind
`make clean && make`

## pegasus

`./pegasus <input_file> <output_file>`
`./secretfind <input_file> <output_file>`

En la primera parte use y me base en la capsula, use para la primera funcion un avl simple usando de criterio la edad y como segundo el id. Para la segunda una construcciono recursiva del arbol hacia arriba cosa de que queden las hojas del arbol ordenadas de menor a mayor peso y como segundo criterio por id, para asi retornar segun los rangos. Para los rectangulos y circulos trate de usar factorial cascading pero no lo implemente del todo bien entonces quedo en un range tree. El tiempo de ejecucion en los tast hard supera los 5 segundos por mucho y nos mantenemos dentro de los paramentros de memoria sin memory leaks. Pero pasamos todos los test cases de manera correcta.

En la segunda parte trate de usar incremental hashing pero parece que no quedo bien implementado porque nos pasamos en los tiempos de ejecucion. No tenemos errores ni fugas de memoria, y tenemos errores en los test cases cuando los arboles son mayores a 15 nodos, Se que no sacamos bien todos los subarboles pero no pude solucionarlo.

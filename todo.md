
# Todo

## VECTOR

[ ] Arreglar destructor

## MAP

### Node
[ ] Arreglar el allocator. Hay que hacer rebind del allocator que le llega.

### Tree
[X] Refactorizar insert. Da asco y no comprueba si un elemento ya existe.
[ ] Refactorizar createEmptyNode. Hay que usar allocator en lugar de new
[ ] Hacer mas pruebas con el nuevo insert y borrar insert2

### Map

[X] Arreglar insert
[X] Insert with hint
[X] Insert range
[X] operator[]
[ ] Cambiar todos tipos que usen std
[ ] Las comparaciones hacerlas con el elemento Compare del map


#### Tal vez
[ ] Refactorizar metodo insert. Hay mucho codigo que se repite en las funciones insert e insertWithHint
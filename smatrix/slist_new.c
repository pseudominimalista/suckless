slist*
slist_new(drop* _drop){
	
	slist *_new = NULL;

	_new = malloc(sizeof(slist));

	_new->next = NULL;
	_new->prev = NULL;
	_new->data = _drop;


	return _new;
}

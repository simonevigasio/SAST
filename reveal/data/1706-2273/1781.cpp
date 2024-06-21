static PyObject * authGSSServerInit ( PyObject * self , PyObject * args ) {
 const char * service = NULL ;
 gss_server_state * state ;
 PyObject * pystate ;
 int result = 0 ;
 if ( ! PyArg_ParseTuple ( args , "s" , & service ) ) return NULL ;
 state = ( gss_server_state * ) malloc ( sizeof ( gss_server_state ) ) ;
 # if PY_MAJOR_VERSION >= 3 pystate = PyCapsule_New ( state , NULL , NULL ) ;
 # else pystate = PyCObject_FromVoidPtr ( state , NULL ) ;
 # endif result = authenticate_gss_server_init ( service , state ) ;
 if ( result == AUTH_GSS_ERROR ) return NULL ;
 return Py_BuildValue ( "(iO)" , result , pystate ) ;
 }
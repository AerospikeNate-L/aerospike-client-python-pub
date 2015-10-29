/*******************************************************************************
 * Copyright 2013-2015 Aerospike, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#include <Python.h>
#include <structmember.h>
#include <stdbool.h>
#include <unistd.h>

#include <aerospike/aerospike.h>
#include <aerospike/as_config.h>
#include <aerospike/as_error.h>
#include <aerospike/as_policy.h>

#include "admin.h"
#include "client.h"
#include "policy.h"
#include "conversions.h"
#include "exceptions.h"
#include "global_hosts.h"

static PyObject * AerospikeGlobalHosts_Type_New(PyTypeObject * type, PyObject * args, PyObject * kwds)
{
	AerospikeGlobalHosts * self = NULL;

	self = (AerospikeGlobalHosts *) PyObject_New(AerospikeGlobalHosts, type);

	if ( self == NULL ) {
		return NULL;
	}

	return (PyObject *) self;
}

/*static int AerospikeGlobalHosts_Type_Init(AerospikeGeospatial * self, PyObject * args, PyObject * kwds)
{
	as_error err;
	as_error_init(&err);

CLEANUP:

	if ( err.code != AEROSPIKE_OK ) {
		PyObject * py_err = NULL;
		error_to_pyobject(&err, &py_err);
		PyObject *exception_type = raise_exception(&err);
		PyErr_SetObject(exception_type, py_err);
		Py_DECREF(py_err);
		return -1;
	}

    return 0;
}*/

static void AerospikeGlobalHosts_Type_Dealloc(PyObject * self)
{
    printf("\nFinal address is: %p\n", (void*) (((AerospikeGlobalHosts* )self)->as)); 
	//self->ob_type->tp_free((PyObject *) self);
	PyMem_DEL((PyObject *) self);
}

/*******************************************************************************
 * PYTHON TYPE DESCRIPTOR
 ******************************************************************************/

static PyTypeObject AerospikeGlobalHosts_Type = {
	PyObject_HEAD_INIT(NULL)

	 .ob_size			= 0,
	.tp_name			= 0,
	.tp_basicsize		= sizeof(AerospikeGlobalHosts),
	.tp_itemsize		= 0,
	.tp_dealloc			= (destructor) AerospikeGlobalHosts_Type_Dealloc,
	.tp_print			= 0,
	.tp_getattr			= 0,
	.tp_setattr			= 0,
	.tp_compare			= 0,
	.tp_repr			= 0,
	.tp_as_number		= 0,
	.tp_as_sequence		= 0,
	.tp_as_mapping		= 0,
	.tp_hash			= 0,
	.tp_call			= 0,
	.tp_str				= 0,
	.tp_getattro		= 0,
	.tp_setattro		= 0,
	.tp_as_buffer		= 0,
	.tp_flags			= Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_doc				=
		"The Global Host stores the persistent objects\n",
	.tp_traverse		= 0,
	.tp_clear			= 0,
	.tp_richcompare		= 0,
	.tp_weaklistoffset	= 0,
	.tp_iter			= 0,
	.tp_iternext		= 0,
	.tp_methods			= 0,
	.tp_members			= 0,
	.tp_getset			= 0,
	.tp_base			= 0,
	.tp_dict			= 0,
	.tp_descr_get		= 0,
	.tp_descr_set		= 0,
	.tp_dictoffset		= 0,
	.tp_init			= 0,
	.tp_alloc			= 0,
	.tp_new				= AerospikeGlobalHosts_Type_New
};

AerospikeGlobalHosts * AerospikeGobalHosts_New(aerospike* as)
{
	AerospikeGlobalHosts * self = (AerospikeGlobalHosts *) AerospikeGlobalHosts_Type.tp_new(&AerospikeGlobalHosts_Type, Py_None, Py_None);
    self->as = as;
    self->shm_key = as->config.shm_key;
    self->ref_cnt = 1;
	return self;
}

void AerospikeGlobalHosts_Del(PyObject *self)
{
    AerospikeGlobalHosts_Type_Dealloc(self);
}

/*
 * Copyright 2003,2004 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <log4cxx/helpers/mutex.h>
#include <log4cxx/helpers/exception.h>
#include <apr_thread_mutex.h>
#include <assert.h>

using namespace log4cxx::helpers;
using namespace log4cxx;


Mutex::Mutex(apr_pool_t* p) {
	apr_status_t stat = apr_thread_mutex_create(&mutex,
		APR_THREAD_MUTEX_NESTED, p);
	if (stat != APR_SUCCESS) {
		throw MutexException(stat);
	}
}

Mutex::~Mutex() {
//	apr_status_t stat = apr_thread_mutex_destroy(mutex);
    //
    //  can't assert that
    //     destroying an unused mutex doesn't return APR_SUCCESS
//	assert(stat == APR_SUCCESS);
}

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

#ifndef _LOG4CXX_HELPERS_MUTEX_H
#define _LOG4CXX_HELPERS_MUTEX_H

#include <log4cxx/portability.h>

extern "C" {
struct apr_thread_mutex_t;
struct apr_pool_t;
}

namespace log4cxx
{
        namespace helpers
        {
                class LOG4CXX_EXPORT Mutex
                {
                public:
                        Mutex(apr_pool_t* p);
                        ~Mutex();

                        inline operator apr_thread_mutex_t*() const { return mutex; }

                private:
                        Mutex(const Mutex&);
                        Mutex& operator=(const Mutex&);
                        apr_thread_mutex_t* mutex;
                };
        } // namespace helpers
} // namespace log4cxx

#endif //_LOG4CXX_HELPERS_MUTEX_H

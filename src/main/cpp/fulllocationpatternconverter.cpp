/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <log4cxx/logstring.h>
#include <log4cxx/pattern/fulllocationpatternconverter.h>
#include <log4cxx/spi/loggingevent.h>
#include <log4cxx/spi/location/locationinfo.h>
#include <log4cxx/helpers/stringhelper.h>

using namespace log4cxx;
using namespace log4cxx::pattern;
using namespace log4cxx::spi;
using namespace log4cxx::helpers;

IMPLEMENT_LOG4CXX_OBJECT(FullLocationPatternConverter)

FullLocationPatternConverter::FullLocationPatternConverter() :
	LoggingEventPatternConverter(LOG4CXX_STR("Full Location"),
		LOG4CXX_STR("fullLocation"))
{
}

PatternConverterPtr FullLocationPatternConverter::newInstance(
	const std::vector<LogString>& /* options */)
{
	static WideLife<PatternConverterPtr> instance = std::make_shared<FullLocationPatternConverter>();
	return instance;
}

void FullLocationPatternConverter::format(
	const LoggingEventPtr& event,
	LogString& toAppendTo,
	Pool& p) const
{
	append(toAppendTo, event->getLocationInformation().getFileName());
	toAppendTo.append(1, (logchar) 0x28 /* '(' */);
	StringHelper::toString(
		event->getLocationInformation().getLineNumber(),
		p, toAppendTo);
	toAppendTo.append(1, (logchar) 0x29 /* ')' */);
}

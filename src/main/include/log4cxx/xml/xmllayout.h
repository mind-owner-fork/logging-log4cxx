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

#ifndef _LOG4CXX_XML_LAYOUT_H
#define _LOG4CXX_XML_LAYOUT_H

#include <log4cxx/layout.h>

namespace log4cxx
{
namespace xml
{

/**
The output of the XMLLayout consists of a series of log4j:event
elements. It does not output a
 complete well-formed XML file. The output is designed to be
included as an <em>external entity</em> in a separate file to form
a correct XML file.

<p>For example, if <code>abc</code> is the name of the file where
the XMLLayout ouput goes, then a well-formed XML file would be:

<code>
<?xml version="1.0" ?>

<!DOCTYPE log4j:eventSet [<!ENTITY data SYSTEM "abc">]>

<log4j:eventSet version="1.2" xmlns:log4j="http://jakarta.apache.org/log4j/">

        @&data;

</log4j:eventSet>
</code>

<p>This approach enforces the independence of the XMLLayout and the
appender where it is embedded.
*/
class LOG4CXX_EXPORT XMLLayout : public Layout
{
	private:
		LOG4CXX_DECLARE_PRIVATE_MEMBER_PTR(XMLLayoutPrivate, m_priv)

	public:
		DECLARE_LOG4CXX_OBJECT(XMLLayout)
		BEGIN_LOG4CXX_CAST_MAP()
		LOG4CXX_CAST_ENTRY(XMLLayout)
		LOG4CXX_CAST_ENTRY_CHAIN(Layout)
		END_LOG4CXX_CAST_MAP()

		XMLLayout();
		~XMLLayout();

		/**
		The <b>LocationInfo</b> option takes a boolean value. By
		default, it is set to false which means there will be no location
		information output by this layout. If the the option is set to
		true, then the file name and line number of the statement
		at the origin of the log statement will be output.

		<p>If you are embedding this layout within a SMTPAppender
		then make sure to set the
		<b>LocationInfo</b> option of that appender as well.
		*/
		void setLocationInfo(bool locationInfo1);

		/**
		Returns the current value of the <b>LocationInfo</b> option.
		*/
		bool getLocationInfo() const;

		/**
		 * Sets whether MDC key-value pairs should be output, default false.
		 * @param flag new value.
		 *
		*/
		void setProperties(bool flag);

		/**
		* Gets whether MDC key-value pairs should be output.
		* @return true if MDC key-value pairs are output.
		*
		*/
		bool getProperties();

		/**
		\copybrief spi::OptionHandler::activateOptions()

		No action is performed in this implementation.
		*/
		void activateOptions(helpers::Pool& /* p */) override { }

		/**
		\copybrief spi::OptionHandler::setOption()

		Supported options | Supported values | Default value
		-------------- | ---------------- | ---------------
		Properties |  True,False | False
		LocationInfo | True,False | False
		*/
		void setOption(const LogString& option,
			const LogString& value) override;

		/**
		* Formats a {@link spi::LoggingEvent LoggingEvent}
		* in conformance with the log4cxx.dtd.
		**/
		void format(LogString& output,
			const spi::LoggingEventPtr& event,
			helpers::Pool& p) const override;

		/**
		The XMLLayout prints and does not ignore exceptions. Hence the
		return value <code>false</code>.
		*/
		bool ignoresThrowable() const override
		{
			return false;
		}

};  // class XMLLayout
LOG4CXX_PTR_DEF(XMLLayout);
}  // namespace xml
} // namespace log4cxx

#endif // _LOG4CXX_XML_LAYOUT_H

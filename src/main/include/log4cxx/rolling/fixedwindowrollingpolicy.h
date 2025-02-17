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

#if !defined(_LOG4CXX_ROLLING_FIXED_WINDOW_ROLLING_POLICY_H)
#define _LOG4CXX_ROLLING_FIXED_WINDOW_ROLLING_POLICY_H

#include <log4cxx/rolling/rollingpolicybase.h>




namespace log4cxx
{

namespace helpers
{
class Pool;
}

namespace rolling
{


/**
 * When rolling over, <code>FixedWindowRollingPolicy</code> renames files
 * according to a fixed window algorithm as described below.
 *
 * <p>The <b>ActiveFileName</b> property, which is required, represents the name
 * of the file where current logging output will be written.
 * The <b>FileNamePattern</b>  option represents the file name pattern for the
 * archived (rolled over) log files. If present, the <b>FileNamePattern</b>
 * option must include an integer token, that is the string "%i" somwhere
 * within the pattern.
 *
 * <p>Let <em>max</em> and <em>min</em> represent the values of respectively
 * the <b>MaxIndex</b> and <b>MinIndex</b> options. Let "foo.log" be the value
 * of the <b>ActiveFile</b> option and "foo.%i.log" the value of
 * <b>FileNamePattern</b>. Then, when rolling over, the file
 * <code>foo.<em>max</em>.log</code> will be deleted, the file
 * <code>foo.<em>max-1</em>.log</code> will be renamed as
 * <code>foo.<em>max</em>.log</code>, the file <code>foo.<em>max-2</em>.log</code>
 * renamed as <code>foo.<em>max-1</em>.log</code>, and so on,
 * the file <code>foo.<em>min+1</em>.log</code> renamed as
 * <code>foo.<em>min+2</em>.log</code>. Lastly, the active file <code>foo.log</code>
 * will be renamed as <code>foo.<em>min</em>.log</code> and a new active file name
 * <code>foo.log</code> will be created.
 *
 * <p>Given that this rollover algorithm requires as many file renaming
 * operations as the window size, large window sizes are discouraged. The
 * current implementation will automatically reduce the window size to 12 when
 * larger values are specified by the user.
 *
 *
 *
 *
 * */
class LOG4CXX_EXPORT FixedWindowRollingPolicy : public RollingPolicyBase
{
		DECLARE_LOG4CXX_OBJECT(FixedWindowRollingPolicy)
		BEGIN_LOG4CXX_CAST_MAP()
		LOG4CXX_CAST_ENTRY(FixedWindowRollingPolicy)
		LOG4CXX_CAST_ENTRY_CHAIN(RollingPolicyBase)
		END_LOG4CXX_CAST_MAP()

		struct FixedWindowRollingPolicyPrivate;

		/**
		 * It's almost always a bad idea to have a large window size, say over 12.
		 */
		enum { MAX_WINDOW_SIZE = 12 };

		bool purge(int purgeStart, int maxIndex, log4cxx::helpers::Pool& p) const;

	public:

		FixedWindowRollingPolicy();
		~FixedWindowRollingPolicy();

		/**
		\copybrief RollingPolicyBase::activateOptions()

		Logs a warning if an option is not valid.

		\sa RollingPolicyBase::activateOptions()
		*/
		void activateOptions(helpers::Pool& p) override;

		/**
		\copybrief RollingPolicyBase::setOption()

		Supported options | Supported values | Default value
		:-------------- | :----------------: | :---------------:
		MinIndex | 1-12 | 1
		MaxIndex | 1-12 | 7
		ThrowIOExceptionOnForkFailure | True,False | True

		\sa RollingPolicyBase::setOption()
		*/
		void setOption(const LogString& option, const LogString& value) override;

		void rollover();

		int getMaxIndex() const;

		int getMinIndex() const;

		void setMaxIndex(int newVal);
		void setMinIndex(int newVal);

		/**
		 * {@inheritDoc}
		 */
		RolloverDescriptionPtr initialize(
			const   LogString&              currentActiveFile,
			const   bool                    append,
			helpers::Pool& pool) override;

		/**
		 * {@inheritDoc}
		 */
		RolloverDescriptionPtr rollover(
			const   LogString&              currentActiveFile,
			const   bool                    append,
			helpers::Pool& pool) override;

	protected:
		/**
		 * A map from "i" and "index" to a integer conversion formatter.
		 *
		 * \sa IntegerPatternConverter
		 */
		log4cxx::pattern::PatternMap getFormatSpecifiers() const override;

};

LOG4CXX_PTR_DEF(FixedWindowRollingPolicy);

}
}

#endif

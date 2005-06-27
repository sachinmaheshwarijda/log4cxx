/*
 * Copyright 1999,2005 The Apache Software Foundation.
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

#ifndef _LOG4CXX_FILTER_ANDFILTER_H
#define _LOG4CXX_FILTER_ANDFILTER_H

#include <log4cxx/spi/filter.h>

namespace log4cxx
{
    namespace filter
    {

/**
 * A filter that 'and's the results of any number of contained filters together.
 *
 * For the filter to process events, all contained filters must return Filter.ACCEPT.
 *
 * If the contained filters do not return Filter.ACCEPT, Filter.NEUTRAL is returned.
 *
 * If acceptOnMatch is set to true, Filter.ACCEPT is returned.
 * If acceptOnMatch is set to false, Filter.DENY is returned.
 *
 * Here is an example config that will accept only events that contain BOTH
 * a DEBUG level AND 'test' in the message:
 *
 *<appender name="STDOUT" class="org.apache.log4j.ConsoleAppender">
 * <filter class="org.apache.log4j.filter.AndFilter">
 *  <filter class="org.apache.log4j.filter.LevelMatchFilter">
 *        <param name="levelToMatch" value="DEBUG" />
 *        <param name="acceptOnMatch" value="true" />
 *  </filter>
 *  <filter class="org.apache.log4j.filter.StringMatchFilter">
 *        <param name="stringToMatch" value="test" />
 *        <param name="acceptOnMatch" value="true" />
 *  </filter>
 *  <param name="acceptOnMatch" value="false"/>
 * </filter>
 * <filter class="org.apache.log4j.filter.DenyAllFilter"/>
 *<layout class="org.apache.log4j.SimpleLayout"/>
 *</appender>
 *
 * To accept all events EXCEPT those events that contain a
 * DEBUG level and 'test' in the message:
 * change the AndFilter's acceptOnMatch param to false and remove the DenyAllFilter
 *
 * NOTE: If you are defining a filter that is only relying on logging event content
 * (no external or filter-managed state), you could opt instead
 * to use an ExpressionFilter with one of the following expressions:
 *
 * LEVEL == DEBUG && MSG ~= 'test'
 * or
 * ! ( LEVEL == DEBUG && MSG ~= 'test' )
 *
 * @author Scott Deboy sdeboy@apache.org
 */
        class LOG4CXX_EXPORT AndFilter:public log4cxx::spi::Filter
        {
          private:
            log4cxx::spi::FilterPtr headFilter;
            log4cxx::spi::FilterPtr tailFilter;
            bool acceptOnMatch;
                 AndFilter(const AndFilter &);
                  AndFilter & operator=(const AndFilter &);


          public:
                  DECLARE_LOG4CXX_OBJECT(AndFilter)
                  BEGIN_LOG4CXX_CAST_MAP()
                  LOG4CXX_CAST_ENTRY(log4cxx::spi::Filter)
                  END_LOG4CXX_CAST_MAP()

                  AndFilter();

            void addFilter(const log4cxx::spi::FilterPtr & filter);

            void setAcceptOnMatch(bool acceptOnMatch);

  /**
   * If this event does not already contain location information,
   * evaluate the event against the expression.
   *
   * If the expression evaluates to true, generate a LocationInfo instance
   * by creating an exception and set this LocationInfo on the event.
   *
   * Returns {@link Filter#NEUTRAL}
   */
            FilterDecision decide(const spi::LoggingEventPtr & event) const;
        };

    }
}
#endif

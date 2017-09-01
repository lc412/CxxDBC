/*
 * EDBStatement.hh
 *
 *  Created on: 2017-5-24
 *      Author: cxxjava@163.com
 */

#ifndef EDB_STATEMENT_HH_
#define EDB_STATEMENT_HH_

#include "Efc.hh"
#include "./ESQLException.hh"
#include "../../../interface/EDBInterface.h"

namespace efc {
namespace edb {

/**
 * <P>The object used for executing a static SQL statement
 * and returning the results it produces.
 * <P>
 * By default, only one <code>ResultSet</code> object per <code>Statement</code>
 * object can be open at the same time. Therefore, if the reading of one
 * <code>ResultSet</code> object is interleaved
 * with the reading of another, each must have been generated by
 * different <code>Statement</code> objects. All execution methods in the
 * <code>Statement</code> interface implicitly close a statment's current
 * <code>ResultSet</code> object if an open one exists.
 *
 * @see Connection#createStatement
 * @see ResultSet
 */

class EConnection;

abstract class EStatement: virtual public EObject {
public:
	virtual ~EStatement();

	/**
	 *
	 */
	EStatement();

	/**
	 *
	 */
	EStatement(EConnection *conn);

	/**
	 * Bind a connection to this.
	 * @param conn The db connection
	 */
	void setConnection(EConnection *conn);

	/**
	 *
	 */
	EConnection* getConnection();

	/**
	 *
	 */
	virtual EStatement& setSql(const char *sql);
	virtual EStatement& setSqlFormat(const char *sqlfmt, ...);

	/**
	 *
	 */
	virtual EStatement& clearSql();

	/**
	 * Bind a sql parameter's value.
	 * @param fieldType The field data type
	 * @param value The value you want to bind
	 * @param size The size of value
	 * @param fieldMaxSize The max size of the table's field,
							 use 0 for the default value
	 * @return true or false
	 */
	virtual EStatement& bind(edb_field_type_e fieldType,
			  	 	 	 const void *value, int size,
			  	 	 	 int fieldMaxSize=0);

	/**
	 * Bind a sql parameter's value.
	 * @param fieldType The field data type
	 * @param value The string you want to bind
	 * @return true or false
	 */
	virtual EStatement& bind(edb_field_type_e fieldType, const char *value);
	/**
	 * Bind a sql parameter's value.
	 * @param fieldType The field data type
	 * @param valueFmt The string format you want to bind string
	 * @param ... The arguments to use while set the data
	 * @return true or false
	 */
	virtual EStatement& bindFormat(edb_field_type_e fieldType, const char *fmt, ...);

	/**
	 *
	 */
	virtual EStatement& bindString(const char* value);
	virtual EStatement& bindBool(boolean value);
	virtual EStatement& bindBool(const char* value);
	virtual EStatement& bindShort(short value);
	virtual EStatement& bindShort(const char* value);
	virtual EStatement& bindInt(int value);
	virtual EStatement& bindInt(const char* value);
	virtual EStatement& bindLong(llong value);
	virtual EStatement& bindLong(const char* value);
	virtual EStatement& bindFloat(float value);
	virtual EStatement& bindFloat(const char* value);
	virtual EStatement& bindDouble(double value);
	virtual EStatement& bindDouble(const char* value);
	virtual EStatement& bindNumeric(llong value);
	virtual EStatement& bindNumeric(const char* value);
	virtual EStatement& bindNumeric(EBigInteger& value);
	virtual EStatement& bindNumeric(EBigDecimal& value);
	virtual EStatement& bindDateTime(EDate* value);
	virtual EStatement& bindDateTime(const char* value);
	virtual EStatement& bindBytes(byte* value, int size);
	virtual EStatement& bindNull();

	/**
	 * Gives the JDBC driver a hint as to the number of rows that should
	 * be fetched from the database when more rows are needed for
	 * <code>ResultSet</code> objects generated by this <code>Statement</code>.
	 * If the value specified is zero, then the hint is ignored.
	 * The default value is zero.
	 *
	 * @param rows the number of rows to fetch
	 * @exception SQLException if a database access error occurs,
	 * this method is called on a closed <code>Statement</code> or the
	 *        condition {@code rows >= 0} is not satisfied.
	 * @since 1.2
	 * @see #getFetchSize
	 */
	virtual void setFetchSize(int rows);

	/**
	 * Retrieves the number of result set rows that is the default
	 * fetch size for <code>ResultSet</code> objects
	 * generated from this <code>Statement</code> object.
	 * If this <code>Statement</code> object has not set
	 * a fetch size by calling the method <code>setFetchSize</code>,
	 * the return value is implementation-specific.
	 *
	 * @return the default fetch size for result sets generated
	 *          from this <code>Statement</code> object
	 * @exception SQLException if a database access error occurs or
	 * this method is called on a closed <code>Statement</code>
	 * @since 1.2
	 * @see #setFetchSize
	 */
	virtual int getFetchSize();

	/**
	 * Execute sql for db exec.
	 * @return true or false
	 */
	virtual EStatement& execute(void) THROWS(ESQLException) = 0;

	/**
	 * Get errmsg after execute sql.
	 * @return The error message string
	 */
	virtual EString getErrorMessage(void) = 0;

	/**
	 * Releases this <code>Statement</code> object's database
	 * and JDBC resources immediately instead of waiting for
	 * this to happen when it is automatically closed.
	 * It is generally good practice to release resources as soon as
	 * you are finished with them to avoid tying up database
	 * resources.
	 * <P>
	 * Calling the method <code>close</code> on a <code>Statement</code>
	 * object that is already closed has no effect.
	 * <P>
	 * <B>Note:</B>When a <code>Statement</code> object is
	 * closed, its current <code>ResultSet</code> object, if one exists, is
	 * also closed.
	 *
	 * @exception SQLException if a database access error occurs
	 */
	virtual void clear() THROWS(ESQLException) = 0;

protected:
	EConnection* connection;
	EBson sqlStmt;
	int sqlCount;
	int fetchSize;
	boolean hasRequestHead;
};

} /* namespace edb */
} /* namespace efc */
#endif /* EDB_STATEMENT_HH_ */

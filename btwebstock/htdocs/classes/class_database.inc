<?php

/*
 * Base class for database access
 *   @abstract
 *
 */
abstract class DataBase {
	protected $_Type = null;
	protected $_Server = 'localhost';
	protected $_Port = 0;
	protected $_User;
	protected $_Password;
	protected $_DBase;
	protected $_connection = false;
	protected $_dataset = false;
	protected $_numrows = -1;

	abstract public function Connect();
	abstract public function executeSQL($_sql);
	abstract protected function SetNumRows();

	public function SetServer($_server){
		$this->_Server = $_server;
	}
	
	public function SetPort($_port){
		$this->_Port = $_port;
	}

	public function SetUser($_user){
		$this->_User = $_user;
	}

	public function SetPassword($_password){
		$this->_Password = $_password;
	}

	public function SetDBase($_dbase){
		$this->_DBase = $_dbase;
	}

	public function startTransaction() {
		$this->executeSQL('START TRANSACTION');
	}

	public function commit() {
		$this->executeSQL('COMMIT');
	}

	public function rollback() {
		$this->executeSQL('ROLLBACK');
	}

	protected function isSELECT($_sql) {
		if(substr(trim(strtolower($_sql)),0,6) == 'select') {
			//We save the DataSet.
			$this->_dataset = $_res;
			//Look for number of registers we got in DataSet.
			$this->SetNumRows();
			return true;
		} else {
			$this->_numrows = -1;
			return false;
		}
	}

	public function getNumRows() {
		return $this->_numrows;
	}

}

/*
 * Class for using with Postgresql (pgsql)
 *
 */
class pgsql extends DataBase {

	public function __construct() {
		$this->_Type = 'pgsql';
	}

	public function Connect() {
		$_strcon = "host={$this->_Server} ";
		$_strcon.= "dbname={$this->_DBase} ";
		$_strcon.= "user={$this->_User} ";

		if($this->_Password != NULL && $this->_Password != "") {
			$_strcon.= "password={$this->_Password} ";
		}

		if(is_int($this->_Port)) {
			$_strcon.= "port={$this->_Port} ";
		}
		$this->_connection = @pg_connect($_strcon);
		return $this->_connection;
	}

	public function executeSQL($_sql) {
		if($this->_connection !== false) {
			$_res = @pg_query($this->_connection, $_sql);
			return $this->_res;
		} else {
			return false;
			}
	}

	protected function SetNumRows() {
		$this->_numrows = ($this->_dataset !== false ? pg_num_rows($this->_dataset) : 0);
	}
}

/*
 * Cass for using with Mysql
 * 
 */
class mysql extends DataBase {

	public function __construct() {
		$this->_Type = 'mysql';
	}

	public function Connect() {
		$this->_connection = new mysqli($this->_Server,
						$this->_User,
						$this->_Password,
						$this->_DBase,
						$this->_Port);
		return $this->_connection;
	}

	public function executeSQL($_sql) {
		if($this->_connection !== false) {
			$_res = @$this->_connection->query($_sql);
			return $this->_res;
		} else {
			return false;
			}
	}

	protected function SetNumRows() {
		$this->_numrows = ($this->_dataset !== false ? $this->_connection->num_rows : 0);
	}

}

?>

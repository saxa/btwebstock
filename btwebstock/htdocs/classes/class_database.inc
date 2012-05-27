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
	protected $_tuple = false;
	protected $_currentpos = -1;
	protected $_lasterror = "";

	abstract public function Connect();
	abstract public function executeSQL($_sql);
	abstract protected function SetNumRows();
	abstract protected function navigateIntern($_pos);
	abstract protected function nextIntern();

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

	public function navigate($_pos = 0) {
		$this->_tuple = false;
		$this->navigateIntern($_pos);
		$this->_currentpos = $_pos;
		return $this->_tuple;
	}

	public function firstPos() {
		return $this->navigate();
	}

	public function nextPos() {
		$this->_tuple = false;
		$this->nextIntern();
		$this->_currentpos++;
		return $this->_tuple;
	}

	public function previousPos() {
		return $this->navigate($this->_currentpos - 1);
	}

	public function lastPos() {
		return $this->navigate($this->_numrows - 1);
	}

	public function getCurrentData() {
		return $this->_tuple;
	}

	public function getLastError() {
		return "[{$this->_Type}]: {$this->_lasterror}";
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
		if(($this->_connection = @pg_connect($_strcon)) === false) {
			$_e = error_get_last();
			$this->_lasterror = "Error connecting to the database: ".
				"{$_e['message']}";
		}
		return $this->_connection;
	}

	public function executeSQL($_sql) {
		if($this->_connection !== false) {
			if(($_res = @pg_query($this->_connection, $_sql)) === false) {
				$this->_lasterror = "Error executing SQL command {$_sql} :" . pg_last_error();
			} else {
				$this->isSELECT($_sql, $_res);
			}
			//return $this->_res;
			return $_res;
		} else {
			return false;
			}
	}

	protected function SetNumRows() {
		$this->_numrows = ($this->_dataset !== false ? pg_num_rows($this->_dataset) : 0);
	}

	protected function navigateIntern($_pos) {
		if(pg_result_seek($this->_dataset, $_pos) !== false) {
			$this->_tuple = pg_fetch_assoc($this->_dataset);
		}
	}

	protected function nextIntern() {
		$this->_tuple = pg_fetch_assoc($this->_dataset);
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
		if(($this->_connection = new mysqli($this->_Server,
						$this->_User,
						$this->_Password,
						$this->_DBase,
						$this->_Port)) === false) {
			$this->_lasterror = "Error connectiong to the database: ". mysqli_connect_error();
		}
		return $this->_connection;
	}

	public function executeSQL($_sql) {
		if($this->_connection !== false) {
			if(($_res = @$this->_connection->query($_sql)) === false) {
				$this->_lasterror = "Error executing SQL command {$_sql} : " . $this->_connection->error;
			}
			$this->isSELECT($_sql, $_res);
			//return $this->_res;
			return $_res;
		} else {
			return false;
			}
	}

	protected function SetNumRows() {
		$this->_numrows = ($this->_dataset !== false ? $this->_connection->num_rows : 0);
	}

	protected function navigateIntern($_pos) {
		if($this->_dataset !== false) {
			if($this->_dataset->data_seek($_pos) !== false) {
				$this->_tuple = $this->_dataset->fetch_assoc();
			}
		}
	}

	protected function nextIntern() {
		if($this->_dataset !== false) {
			$this->_tuple = $this->_dataset->fetch_assoc();
		}
	}

}

?>

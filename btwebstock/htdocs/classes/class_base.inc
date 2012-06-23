<?php
/* Copyright (C) 2012	Sasa Ostrouska	<casaxa@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 *
 * Abstract class for field generation in the framework.
 *
 */

abstract class field {

	protected $_name;
	protected $_title;
	protected $_type;
	protected $_size;
	protected $_format;
	protected $_relation;
	protected $_include;
	protected $_alterate;
	protected $_list;
	protected $_min;
	protected $_max;
	protected $_fieldref;
	protected $_value;
	protected $_previous_value;
	protected $_pk;
	/*
	 * @var DataBase $_connection
	 */
	protected $_connection = null;

	abstract public function toDB();
	abstract public function toHTML();

	/*
	 * Class constructor
	 *
	 * @param string  $_name
	 * @param string  $_title
	 * @param string  $_type
	 * @param integer $_size
	 * @param string  $_format
	 * @param string  $_relation
	 * @param bool    $_include
	 * @param bool    $_alterate
	 * @param bool    $_list
	 * @param string  $_min
	 * @param string  $_max
	 * @param string  $_fieldref
	 * @param database $_connection
	 *
	 */
	public function __construct($_name, $_title, $_type,
					$_size, $_format, $_relation,
					$_include=true, $_alterate=true, $_list=true,
					$_min=null, $_max=null, $_fieldref=null,
					$_pk=false, database &$_connection=null) {
		$this->_name		= $_name;
		$this->_title		= $_title;
		$this->_size		= $_size;
		$this->_format		= $_format;
		$this->_relation	= $_relation;
		$this->_include		= (bool) $_include;
		$this->_alterate	= (bool) $_alterate;
		$this->_list		= (bool) $_list;
		$this->_min		= $_min;
		$this->_max		= $_max;
		$this->_fieldref	= $_fieldref;
		$this->_value		= null;
		$this->_connection	= $_connection;
		$this->_pk		= (bool) $_pk;
	}

	public function __call($_method, $_values) {
		$_m = strtolower($_method);
		switch(substr($_m, 0, 3)) {
			case 'get':
			case 'set':	$_attribute = "_" . substr($_m, 3);
					if(property_exists($this, $_attribute)) {
						return $this->{$_attribute};
					} else {
						return false;
					}
					break;
		}
		return false;
	}

}

/*
 *
 * Class for generating fields of type string.
 *
 */
class string extends field {

	public function __construct($_name, $_title,
					$_size, $_format, $_relation,
					$_include=true, $_alterate=true, $_list=true,
					$_min=null, $_max=null, $_fieldref=null,
					$_pk=false, database &$_connection=null) {
		parent::__construct($_name, $_title, 'STR',
					$_size, $_format, $_relation,
					$_include, $_alterate, $_list, $_min, $_max=null,
					$_fieldref, $_pk, $_connection);
		}
	public function toDB() {
		return "'" . $this->_connection->escpeString($this->_value) . "'";
	}

	public function toHTML() {
		return $this->_value;
	}
}

/*
 *
 * Class for generating of numeric fields.
 *
 */
class number extends field {

	protected $_decimal_places = 99;

	public function __construct($_name, $_title, $_type,
					$_size, $_format, $_relation,
					$_include=true, $_alterate=true, $_list=true,
					$_min=null, $_max=null, $_fieldref=null, $_pk=false) {
		parent::__construct($_name, $_title, $_type,
					$_size, $_format, $_relation,
					$_include, $_alterate, $_list, $_min,
					$_max=null, $fieldref=null, $_pk);
	}

	public function toDB() {
		return number_format(str_replace("," , ".", 
					str_replace(".", "", $this->_value)),
					$this->_decimal_places, ".", "");
	}

	public function toHTML() {
		return number_format($this->_value, $this->_decimal_places, ",", "");
	}

	public function getExtraAttributes() {
		return new attribute("ALIGN", "RIGHT");
	}
}

/*
 *
 * Class derived from class number for generating integers.
 *
 */
class integer extends number {

	public function __construct($_name, $_title, 
					$_size, $_format, $_relation, 
					$_include=true, $_alterate=true, $_list=true,
					$_min=null, $_max=null, $_fieldref=null, $_pk=false) {
		parent::__construct($_name, $_title, 'INT',
					$_size, $_format, $_relation,
					$_include, $_alterate, $_list, $_min,
					$_max=null, $fieldref=null, $_pk);
		$this->_decimal_places = 0;
	}
}

/*
 *
 * Class derived from clas number for generating floating point numbers.
 *
 */
class float extends number {

	public function __construct($_name, $_title, 
					$_size, $_format, $_relation, 
					$_include=true, $_alterate=true, $_list=true,
					$_min=null, $_max=null, $_fieldref=null, 
					$_pk=false, $_dplaces=3) {
		parent::__construct($_name, $_title, 'FLT',
					$_size, $_format, $_relation,
					$_include, $_alterate, $_list, $_min,
					$_max=null, $fieldref=null, $_pk);
		$this->_decimal_places = $_dplaces;
	}
}

/*
 *
 * Class derived from class number for generating values of type Money.
 *
 */
class money extends number {

	public function __construct($_name, $_title, 
					$_size, $_format, $_relation, 
					$_include=true, $_alterate=true, $_list=true,
					$_min=null, $_max=null, $_fieldref=null, 
					$_pk=false) {
		parent::__construct($_name, $_title, 'CUR',
					$_size, $_format, $_relation,
					$_include, $_alterate, $_list, $_min,
					$_max=null, $fieldref=null, $_pk);
		$this->_decimal_places = 2;
	}
}

/*
 *
 * Class for generating the fields of type date. (Without information of time.)
 *
 */
class date extends field {

	public function __construct($_name, $_title, 
					$_size, $_format, $_relation,
					$_include=true, $_alterate=true, $_list=true,
					$_min=null, $_max=null, $_fieldref=null,
					$_pk=false, database &$_connection=null) {

		parent::__construct($_name, $_title, 'DATE',
					$_size, $_format, $_relation,
					$_include, $_alterate, $_list, $_min,
					$_max=null, $_fieldref=null, $_pk, $_connection);
	}

	public function toDB() {
		return $this->_connection->convertDataToDB($this->_value);
	}
	
	public function toHTML() {
		return $this->_connection->convertDataToHTML($this->_value);
	}
}

/*
 *
 * Class for generating the fields of type date and time.
 *
 */
class date_time extends field {

	public function __construct($_name, $_title, 
					$_size, $_format, $_relation,
					$_include=true, $_alterate=true, $_list=true,
					$_min=null, $_max=null, $_fieldref=null,
					$_pk=false, database &$_connection=null) {

		parent::__construct($_name, $_title, 'DTIME',
					$_size, $_format, $_relation,
					$_include, $_alterate, $_list, $_min,
					$_max=null, $_fieldref=null, $_pk, $_connection);
	}

	public function toDB() {
		return $this->_connection->convertDataTimeToDB($this->_value);
	}
	
	public function toHTML() {
		return $this->_connection->convertDataTimeToHTML($this->_value);
	}
}

/*
 *
 * Base class
 *
 */
class Base {

	protected $_table_name;
	protected $_fields = Array();
	/*
	 * @var DataBase
	 */
	protected $_connection = null;

	public function __construct(DataBase &$_connection = null) {
		$this->_connection = $_connection;
	}

	public function addField(field $_field) {
		$this->_fields[$_field->getName()] = $_field;
	}

	public function deleteField($_field) {
		unset($this->_fields[$_field]);
	}

	public function clearFields() {
		$this->_fields = Array();
	}

	public function getField($_field) {
		return $this->_fields[$_field];
	}

	public function filterFields($_filter="list", $_value=true) {
		$_fields = Array();
		foreach($this->_fields as $_field) {
			$_fcn = "get{$_filter}";
			if($_field->$_fcn() === $_value) {
				$_fields[$_field->getName()] = $_field;
			}
		}
		return $_fields;
	}
	
	public function createSELECT($_fields, $_where=null,
					$_orderby=null,
					$_limit=null,
					$_extras=null) {
		return "SELECT {$_fields} FROM {$this->_table_name} " .
			($_where !== null ? "WHERE {$_where}" : "" ) .
			($_orderby !== null ? " ORDER BY {$_orderby}" : "" ) .
			($_extras !== null ? " {$_extras}" : "" ) .
			($_limit !== null ? " LIMIT {$_limit}" : "" );
	}

	public function listStuff() {
		$_listoffields = array_merge($this->filterFields(), $this->filterFields("pk"));
		$_strSQL = $this->createSELECT(implode(",", array_keys($_listoffields)));
		$_types = new standardtypes();
		// Header of the HTML TABLE
		$_tab = new tag($_types->getType('TABLE'),
				Array(new attribute("BORDER", 0),
				new attribute("CELLPADDING", 5),
				new attribute("STYLE", "border:1px   solid   #a0a0a0;" . "border-collapse:collapse;"),
				new attribute("WIDTH", "100%")));
		$_tr = new tag($_types->getType('TR'));
		foreach($_listoffields as $_field) {
			$_tr->addSubTag(new tag($_types->getType('TH'),
				Array(new attribute("STYLE", "border:1px" . "solid #a0a0a0;" . "background-color:#f0f0f0;")),
				$_field->getTitle()));
		}
		$_tab->addSubTag($_tr);

		if($this->_connection->executeSQL($_strSQL) !== false && $this->_connection->getNumRows() > 0) {
			$_c = 0;
			while($this->nextPos()) {
				$_det[$_c] = new tag($_types->getType('TR'));
				foreach($_listoffields as $_field) {
					$_det[$_c]->addSubTag(new tag($_types->getType('TD'),
						Array(new attribute("STYLE", "border:1px" . "solid #a0a0a0;"), 
						$_field->getExtraAttributes()),
						$_field->toHTML()));
				}
				$_tab->addSubTag($_det[$_c]);
				++$_c;
			}
			$_trf = new tag($_types->getType('TR'));
			$_trf->addSubTag(new tag($_types->getType('TD'),
						Array(new attribute("COLSPAN", sizeof($_listoffields)),
							new attribute("STYLE", "color:#a0a0a0;font-size:11px;" . "border:1px solid #a0a0a0;")),
						"Total of {$this->_connection->getNumRows()} registers"));
			$_tab->addSubTag($_trf);
		} else {
			$_trf = new tag($_types->getType('TR'));
			$_trf->addSubTag(new tag($_types->getType('TD'),
						Array(new attribute("COLSPAN", sizeof($_listoffields)),
							new attribute("STYLE", "border:1px solid #a0a0a0;" . "text-align:center")),
						"No registers"));
			$_tab->addSubTag($_trf);
		}
		return $_tab->toHTML();
	}
	
	public function fillField($_d) {
		foreach($this->_fields as $_k => $_field) {
			$this->_fields[$_k]->setValue($_d[$_k]);
		}
	}

	public function nextField() {
		if(($_d = $this->_connection->nextPos()) !== false) {
			$this->fillField($_d);
			return true;
		} else {
			return false;
		}
	}
}

?>

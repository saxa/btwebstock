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
					$_min=null, $_max=null, $fieldref=null,
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
					$_min=null, $_max=null, $fieldref=null,
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

?>

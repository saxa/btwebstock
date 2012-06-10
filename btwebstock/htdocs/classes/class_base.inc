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

?>

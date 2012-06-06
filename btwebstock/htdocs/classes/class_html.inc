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
 * Define the types of the available HTML TAGs.
 *
 */

class typetag {

	protected $_name;
	protected $_finalize = true;

	public function __construct($_name, $_finalize = true) {
		$this->_name = $_name;
		$this->_finalize = (bool) $_finalize;
		return $this;
	}

	public function getName() {
		return $this->_name;
	}

	public function getFinalize() {
		return (bool) $this->_finalize;
	}
}

class standardtypes {

	private $_types = Array();

	public function __construct() {
		$this->initialize();
	}

	public function initialize() {
		$this->_types = Array(	"HTML"=>new typetag("HTML"),
					"HEAD"=>new typetag("HEAD"),
					"TITLE"=>new typetag("TITLE"),
					"LINK"=>new typetag("LINK", false),
					"BODY"=>new typetag("BODY"),
					"TABLE"=>new typetag("TABLE"),
					"TBODY"=>new typetag("TBODY"),
					"TR"=>new typetag("TR"),
					"TH"=>new typetag("TH"),
					"TD"=>new typetag("TD"),
					"A"=>new typetag("A"),
					"BR"=>new typetag("BR", false),
					"FORM"=>new typetag("FORM"),
					"INPUT"=>new typetag("INPUT", false),
					"SELECT"=>new typetag("SELECT"),
					"OPTION"=>new typetag("OPTION"),
					"TEXTAREA"=>new typetag("TEXTAREA"),
					"IMG"=>new typetag("IMG"),
					"DIV"=>new typetag("DIV"),
					"SPAN"=>new typetag("SPAN"),
					"BUTTON"=>new typetag("BUTTON"),
					"SCRIPT"=>new typetag("SCRIPT"),
					"META"=>new typetag("META", false),
					"COMMENT"=>new typetag("COMMENT", false),
					"HR"=>new typetag("HR", false),
					"P"=>new typetag("P"),
					"MAP"=>new typetag("MAP"),
					"IFRAME"=>new typetag("IFRAME"),
					"AREA"=>new typetag("AREA", false),
					"BASE"=>new typetag("BASE", false),
					"STYLE"=>new typetag("STYLE")
				);
	}

	public function getType($_type) {
		return $this->_types[$_type];
	}
}

/*
 * Defines an attribute for the related html marker.
 *
 */
class attribute {

	protected $_name;
	protected $_value;

	public function __construct($_name, $_value=null) {
		$this->_name = $_name;
		$this->_value = $_value;
		return $this;
	}

	public function getAttribute() {
		// Returns format attribute.name[=attribute.value]
		return " {$this->_name}" . ($this->_value!==null ? "=\"{$this->_value}\"" : "");
	}
}


?>

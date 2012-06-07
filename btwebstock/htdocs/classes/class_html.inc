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

/*
 * Class which holds the HTML tags.
 *
 */
class tag {

	protected $_type;
	protected $_attributes = Array();
	protected $_value;
	protected $_subtags = Array();

	public function __construct(typetag $_type, $_attributes = Array(), $_value = null) {
		$this->_type = $_type;
		$this->_attributes = (is_array($_attributes) ? $_attributes : Array() );
		$this->_value = $_value;
		return $this;
	}

	public function setValue($_value) {
		$this->_value = $_value;
	}

	public function append($_value) {
		$this->_value .= $_value;
	}

	public function addAttribute(attribute $_attribute = null) {
		$this->_attributes[] = $_attribute;
		return sizeof($this->_attributes) - 1;
	}

	public function deleteAttribute($_attribute) {
		unset( $this->_attributes[$_attribute] );
	}

	public function clearAttributes() {
		$this->_attributes = Array();
	}

	public function addSubTag(tag $_subtag) {
		$this->_subtags[] = $_subtag;
		return sizeof($this->_subtags) - 1;
	}

	public function deleteSubTag($_id) {
		unset($this->_subtags[$_id]);
	}

	public function clearSubTags() {
		$this->_subtags = Array();
	}

	public function toHTML() {
		$_html = "<{$this->_type->getName()}";
		foreach($this->_attributes as $_att) {
			$_html .= $_att->getAttribute();
		}
		$_html .= ">{$this->_value}";
		foreach($this->_subtags as $_subtag) {
			$_html .= $_subtag->toHTML();
		}
		$_html .= ($this->_type->getFinalize() === true ? "</{$this->_type->getName()}>" : "");
		return $_html;
	}
}

/*
 *
 * Class for generating HTML code.
 *
 */
class html {

	protected $_tags = Array();

	public function addTag(tag $_tag) {
		$this->_tags[] = $_tag;
		return sizeof($this->_tags) - 1;
	}

	public function deleteTag($_id) {
		unset($this->_tags[$_id]);
	}

	public function toHTML() {
		$_html = "";
		foreach($this->_tags as $_tag) {
			$_html .= $_tag->toHTML();
		}
		return $_html;
	}
}


?>

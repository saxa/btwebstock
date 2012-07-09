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

class pagination {

	const REGISTERS_PER_PAGE = 25;
	const INTERVAL = 16;

	private function getListOfPages($_current_page, $_nr_of_pages) {
		$_pages = Array();

		if($_current_page > 1 && $_nr_of_pages > self::INTERVAL) {
			$_pages[] = "1";
			$_pages[] = "...";
		}

		$_last_page = $_current_page + self::INTERVAL - 1;

		if($_last_page > $_nr_of_pages) {
			$_last_page = $_nr_of_pages;
		}

		if($_nr_of_pages - $_current_page < self::INTERVAL) {
			$_current_page = $_nr_of_pages - self::INTERVAL;
			if($_current_page < 1) {
				$_current_page = 1;
			}
		}
		
		for($_page = $_current_page; $_page <= $_last_page; $_page++) {
			$_pages[] = $_page;
		}

		if($_last_page !=  $_nr_of_pages) {
			$_pages[] = "...";
			$_pages[] = $_nr_of_pages;
		}

		return $_pages;
	}

	private function includeLink($_pages, $_current_page, $_total_registers) {

		$_previous_page = 1;
		foreach($_pages as $_idx=>$_page) {
			$_goto = ($_page == "...") ? floor(($_pages[$_idx + 1] - $_previous_page) / 2) + $_previous_page : $_page;
			$_page = ($_page == $_current_page ? "<span style='font-size:18px;" .
								"vertical-align:middle;" .
								"border:1px solid #990033;" .
								"pading:2px;font-weight:bold;" .
								"color:#990033;'> {$_page} </span>"
							   : "<span style='font-size:13px;" .
							   	"vertical-align:middle;'>" .
								" {$_page} </span>");
			$_pages[$_idx] = "<a href=\"{$_SERVER['PHP_SELF']}?" .
					"page={$_goto}&" .
					"total_registers={$_total_registers}\"" .
					" style='text-decoration:none;" .
					"color:Navy;'> {$_page} </a>";
			$_previous_page = $_goto;
		}

		return $_pages;
	}

	public static function paginate($_total_registers, $_current_page, $_registers_per_page=null) {
		
		if((int)$_registers_per_page <= 0) {
			$_registers_per_page = self::REGISTERS_PER_PAGE;
		}

		$_nr_of_pages = ceil($_total_registers / $_registers_per_page);
		return self::includeLink(self::getListOfPages($_current_page, $_nr_of_pages), $_current_page, $_total_registers);
	}

	public static function getLimit($_page) {
		$_page = $_page > 0 ? $_page : 1;
		return array("LIMIT"=>self::REGISTERS_PER_PAGE, "OFFSET"=>($_page - 1) * self::REGISTERS_PER_PAGE);
	}

}

?>

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

$debug = 1;

$currentdir = getcwd();
$includesdir = $currentdir."/../classes/";

if ($debug){
	echo $includesdir."<br>";
}

include_once($includesdir."class_database.inc");
include_once($includesdir."class_html.inc");
include_once($includesdir."class_base.inc");

$_db = new pgsql();
$_db->SetServer('localhost');
$_db->SetDBase('db_btwebstock');
$_db->SetUser('postgres');
$_db->SetPassword('postgres');
$_db->SetPort(5432);
$_db->Connect() or die($_db->getLastError());

$_db->startTransaction();

for($_i=1000; $_i<=2000; $_i++) {
	$_sql = "insert into tab_test values({$_i}," . "'Element {$_i}'," . (mt_rand(1,10000) / 1000) .")";
	echo $_sql;
	var_dump($_db->executeSQL($_sql));
	echo $_db->getLastError();
	echo "<BR>";
}

$_db->commit();

?>

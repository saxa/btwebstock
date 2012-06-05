<?php

/*
 * Example of database use
 *
 */
$debug = 1;

$currentdir = getcwd();
$includesdir = $currentdir."/../classes/";

if ($debug){
	echo $includesdir."<br>";
}

include_once($includesdir."class_database.inc");

$_db = new pgsql();
$_db->SetServer('localhost');
$_db->SetDBase('db_btwebstock');
$_db->SetUser('postgres');
$_db->SetPassword('postgres');
$_db->SetPort(5432);
//var_dump($_db->Connect());
//	echo "You have fucked up something. Go and debug.";
$_db->Connect() or die($_db->getLastError());

$_sql = "SELECT * FROM tab_test";
$_db->executeSQL($_sql);

echo "Number of registers returned by SELECT:{$_db->getNumRows()}<br>";
echo "<table border=1 cellpadding=5 width=400>
	<tr>
		<th>Code</th>
		<th>Description</th>
		<th>Value</th>
	</tr>";

while($_d = $_db->nextPos()) {
	echo "	<tr>
			<td>{$_d['code']}<i/td>
			<td>{$_d['description']}</td>
			<td align='right'>{$_d['value']}</td>
		</tr>";
}
echo "</table>";

?>

<?php

/*
 * Example of database use
 *
 */
$debug = 1;

$currentdir = getcwd();
$includesdir = $currentdir."/classes/";

if ($debug){
	echo $includesdir."<br>";
}

include_once($includesdir."class_database.inc");

$_db = new mysql();
$_db->SetServer('localhost');
$_db->SetDBase('db_btwebstock_test');
$_db->SetUser('root');
$_db->SetPassword('mysqlrootpa55word');
$_db->SetPort(3306);
$_db->Connect();

$_sql = "SELECT * FROM table_test";
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
			<td>{$_d['code']}</td>
			<td>{$_d['description']}</td>
			<td align='right'>{$_d['value']}</td>
		</tr>";
}
echo "</table>";

?>

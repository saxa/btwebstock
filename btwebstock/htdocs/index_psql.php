<?php

/*
 * Example of database use
 *
 */
$debug = 0;

$currentdir = getcwd();
$includesdir = $currentdir."/classes/";

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
$_db->Connect();

$_sql = "create table tab_test(code int4 default 0, description varchar(20), valor float, primary key(code))";
if($_db->executeSQL($_sql)!== false) {
	echo "Table sucessfully created !<br>";
}

$_sql = "insert into tab_test values (1, 'test', 1,5)";
if($_db->executeSQL($_sql) !== false) {
	echo "1st register inserted.<br>";
}

$_sql = "insert into tab_test values (2, 'test', 3,5)";
if($_db->executeSQL($_sql) !== false) {
	echo "2nd register inserted.<br>";
}
$_sql = "insert into tab_test values (3, 'test', 7,15)";
if($_db->executeSQL($_sql) !== false) {
	echo "3rd register inserted.<br>";
}

?>

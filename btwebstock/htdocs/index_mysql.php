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

$_db = new mysql();
$_db->SetServer('localhost');
$_db->SetDBase('db_btwebstock_test');
$_db->SetUser('root');
$_db->SetPassword('mysqlrootpa55word');
$_db->SetPort(3306);
$_db->Connect();


$_sql = "create table table_test(
	code int4 default 0, 
	description varchar(20), 
	value float, 
	primary key(code))";
if($_db->executeSQL($_sql)!== false) {
	echo "Table sucessfully created !<br>";
}

$_sql = "insert into table_test(code, description, value) values (1, 'testdesc', 1.55)";
if($_db->executeSQL($_sql) !== false) {
	echo "1st register inserted.<br>";
}

$_sql = "insert into table_test(code, description, value) values (2, 'testdesc1', 11.65)";
if($_db->executeSQL($_sql) !== false) {
	echo "2nd register inserted.<br>";
}

$_sql = "insert into table_test(code, description, value) values (3, 'testdesc2', 81.45)";
if($_db->executeSQL($_sql) !== false) {
	echo "3rd register inserted.<br>";
}

?>

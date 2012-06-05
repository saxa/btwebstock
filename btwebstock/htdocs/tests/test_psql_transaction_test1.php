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
$_db->Connect();

$_db->startTransaction();
$_sql = "insert into tab_test values (10, 'test 10 desc', 15.3)";
$_db->executeSQL($_sql);
$_sql = "delete from tab_test where code=1";
$_db->executeSQL($_sql);
$_db->commit();

?>

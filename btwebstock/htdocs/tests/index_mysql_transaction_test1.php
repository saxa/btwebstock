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

$_db->startTransaction();
$_sql = "insert into table_test values (10, 'test 10 desc', 15.3)";
$_db->executeSQL($_sql);
$_sql = "delete from table_test where code=1";
$_db->executeSQL($_sql);
$_db->commit();

?>

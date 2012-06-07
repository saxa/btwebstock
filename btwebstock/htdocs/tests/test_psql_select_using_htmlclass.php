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
include_once($includesdir."class_html.inc");

$_db = new pgsql();
$_db->SetServer('localhost');
$_db->SetDBase('db_btwebstock');
$_db->SetUser('postgres');
$_db->SetPassword('postgres');
$_db->SetPort(5432);
$_db->Connect() or die($_db->getLastError());

$_sql = "SELECT * FROM tab_test";
$_db->executeSQL($_sql) or die($_db->getLastError());

$_html = new html();
$_types = new standardtypes();
$_tag1 = new tag($_types->getType('HTML'));
$_body = new tag($_types->getType('BODY'));
$_body->addSubTag(new tag($_types->getType('P'), null, "Number of registers returned by SELECT: {$_db->getNumRows()}"));
$_tab = new tag($_types->getType('TABLE'),
		Array(new attribute("BORDER", 1),
		new attribute("CELLPADDING", 5),
		new attribute("WIDTH", 400)));
$_tr = new tag($_types->getType('TR'));
$_tr->addSubTag(new tag($_types->getType('TH'), null, 'Code'));
$_tr->addSubTag(new tag($_types->getType('TH'), null, 'Description'));
$_tr->addSubTag(new tag($_types->getType('TH'), null, 'Value'));
$_tab->addSubTag($_tr);
$_tag1->addSubTag($_body);
$_html->addTag($_tag1);

$_c = 0;
while($_d = $_db->nextPos()) {
	$_det[$_c] = new tag($_types->getType('TR'));
	$_det[$_c]->addSubTag(new tag($_types->getType('TD'), null, $_d['code']));
	$_det[$_c]->addSubTag(new tag($_types->getType('TD'), null, $_d['description']));
	$_det[$_c]->addSubTag(new tag($_types->getType('TD'), Array(new attribute('ALIGN', 'right')), $_d['value']));
	$_tab->addSubTag($_det[$_c]);
	++$_c;
}

$_body->addSubTag($_tab);

$_html->setOptimized(false);
echo $_html->toHTML();

?>

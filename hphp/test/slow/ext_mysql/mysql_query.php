<?hh
<<__EntryPoint>> function main(): void {
require_once('connect.inc');
list($host, $user, $passwd, $db) = connection_settings();
$conn = mysql_connect($host, $user, $passwd);
var_dump(create_test_table($db, 'query'));
var_dump(mysql_query(
  "insert into test_query (name) values ('test'),('test2')"));

$res = mysql_query('select * from test_query');
$row = mysql_fetch_assoc($res);
print_r($row);

$row = mysql_fetch_assoc($res);
print_r($row);

$row = mysql_fetch_assoc($res);
var_dump($row);
}

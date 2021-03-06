<?hh
/* Prototype  : int imagecolorallocate(resource im, int red, int green, int blue)
 * Description: Allocate a color for an image
 * Source code: ext/gd/gd.c
 */
<<__EntryPoint>> function main(): void {
$red = 10;
$green = 10;
$blue = 10;
$extra_arg = 10;
$im = imagecreate(200, 200);

echo "*** Testing imagecolorallocate() : error conditions ***\n";

//Test imagecolorallocate with one more than the expected number of arguments
echo "\n-- Testing imagecolorallocate() function with more than expected no. of arguments --\n";
try { var_dump( imagecolorallocate($im, $red, $green, $blue, $extra_arg) ); } catch (Exception $e) { echo "\n".'Warning: '.$e->getMessage().' in '.__FILE__.' on line '.__LINE__."\n"; }

// Testing imagecolorallocate with one less than the expected number of arguments
echo "\n-- Testing imagecolorallocate() function with less than expected no. of arguments --\n";
try { var_dump( imagecolorallocate() ); } catch (Exception $e) { echo "\n".'Warning: '.$e->getMessage().' in '.__FILE__.' on line '.__LINE__."\n"; }
try { var_dump( imagecolorallocate($im, $red, $green) ); } catch (Exception $e) { echo "\n".'Warning: '.$e->getMessage().' in '.__FILE__.' on line '.__LINE__."\n"; }
echo "===DONE===\n";
}

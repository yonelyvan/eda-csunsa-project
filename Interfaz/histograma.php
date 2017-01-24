<?php

$filename= "img0.ppm";
$file_img = fopen("img0.ppm", "r");
//$file_hist= fopen("features.txt" ,'w');
$HISTO;
$x; $y;
$linea = fgets($file_img);
$linea = fgets($file_img);
$token = explode(" ",$linea);
$tk = explode("\n",$token[1]); 
$x = $token[0]; 
$y = $tk[0]; 
echo $x ;
echo $y ;

$z = fgets($file_img);
$tam= 256;
$abs=array_fill(0, $x, 0);
$ord= array_fill(0, $y, 0);
//print_r( $abs) ;
//print_r( $ord );
$R = array_fill(0, $x, array_fill(0, $y, 0));
$G ; $B;
$HR =array_fill(0, $tam, 0);
$HG = array_fill(0, $tam, 0);
$HB = array_fill(0, $tam, 0);

//print_r($HR);
$content = fread($file_img, filesize($filename));
$lines = explode(" ", $content);
//print_r($lines);
$t=0;

for ($i = 0; $i < $x; $i++) 
{
	for ($j = 0; $j < $y; $j++) 
	{
			$R[$i][$j] = $lines[$t];
			$val = $R[$i][$j];
			$HR[intval($val)] ++;
			$t++;

			$G[$i][$j] = $lines[$t];
			$val = $G[$i][$j];
			$HG[intval($val)]++;
			$t++;

			$B[$i][$j] = $lines[$t];
			$val = $B[$i][$j];		
			$HB[intval($val)]++;
			$t++;
	}
}


echo '{';
for ($i = 0; $i < $tam; $i++) 
{
	$prom= (intval($HR[$i]+ $HG[$i] + $HB[$i])/3);
	if($i == 255)
	{
		$HISTO[$i]=$prom;
		echo $HISTO[$i]; 	
		break;
	}
	$HISTO[$i] = $prom;
	echo $HISTO[$i]."\n" ;
	echo "\t";
}









/*

for ($i = 0; $i < $x; $i++) 
{
	for ($j = 0; $j < $y; $j++) 
	{
		for ($k = $t; $k < $t+3; $k++ )
		{ 
			echo "entra";
			//$R[$i][$j] = $tmp2[0];
			/*$HR[($R[$i][$j])]+=1;

			$G[$i][$j] = $tmp2[$k+1];
			$HG[($G[$i][$j])]+=1;

			$B[$i][$j] = $tmp2[$k+2];		
			$HB[($B[$i][$j])]+=1;

	}
}
*/



?>
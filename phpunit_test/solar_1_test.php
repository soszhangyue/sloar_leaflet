<?php
use PHPUnit\Framework\TestCase;

require_once('solar_1.php');

class Leaflet_Map_SpotTest extends TestCase{

	public function setUp(){}
	public function tearDown(){}
	public function testInit(){
		$location=array(//Testdata
			array(-15.601,-47.713),
			array(60.1389,-1.1847),
			array(-89.983,-24.799),
			array(43.73,-96.62),
			array(22.7903,5.5292),
			array(32892,123),//wrong input
		);
		for ($i=0; $i <5; $i++) { 
			$Spot=new Leaflet_Map_Spot($location[$i][0],$location[$i][1]);
			$this->assertTrue(is_numeric($Spot->lat));
			$this->assertTrue(is_numeric($Spot->lon));
			unset($Spot);
		}
		$Spot=new Leaflet_Map_Spot($location[5][0],$location[5][1]);
		$this->assertEquals("Wrong Input",$Spot->error_log);
		unset($Spot);

	}
	public function testInf_Match(){
		$location=array(//Testdata
			array(-15.601,-47.713,'Brasilia'),
			array(60.1389,-1.1847,'Lerwick'),
			array(-89.983,-24.799,'South_Pole'),
			array(43.73,-96.62,'Sioux_Falls'),
			array(22.7903,5.5292,'Tamanrasset'),
			array(12,123),//wrong input
		);
		for ($i=0; $i <5; $i++) { 
			$Spot=new Leaflet_Map_Spot($location[$i][0],$location[$i][1]);
			$Spot->Inf_Match();
			$this->assertEquals($location[$i][2],$Spot->Location);
		}
		$Spot=new Leaflet_Map_Spot($location[5][0],$location[5][1]);
		$Spot->Inf_Match();
		$this->assertEquals("Can't Match Any Spot In Database",$Spot->error_log);
		unset($Spot);
	}
}
?>
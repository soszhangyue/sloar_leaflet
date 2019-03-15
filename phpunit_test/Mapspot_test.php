<?php
use PHPUnit\Framework\TestCase;

require 'Mapspot.php';

class Leaflet_Map_SpotTest extends TestCase{

	public function setUp(){}
	public function tearDown(){}
	public function testInit(){// initiate a new class , -90<lat<90,-180<lon<180; lat lon need to be numeric;
		$location=array(//Testdata
			array(-15.601,-47.713),
			array(60.1389,-1.1847),
			array(-89.983,-24.799),
			array(43.73,-96.62),
			array(22.7903,5.5292),
			array(32892,123),//wrong input 
		);
		for ($i=0; $i <5; $i++) { 
			$Spot=new Leaflet_Map_Spot($location[$i][0],$location[$i][1]);//if lat lon are numeric
			$this->assertTrue(is_numeric($Spot->lat));
			$this->assertTrue(is_numeric($Spot->lon));
			unset($Spot);
		}
		$Spot=new Leaflet_Map_Spot($location[5][0],$location[5][1]);//wrong input test
		$this->assertEquals("Error:Wrong Input",$Spot->error_log);
		unset($Spot);

	}
	public function testInf_Match(){//match a mapspot 
		$location=array(//Testdata
			array(-15.601,-47.713,'Brasilia'),//lat,lon,location
			array(60.1389,-1.1847,'Lerwick'),
			array(-89.983,-24.799,'South_Pole'),
			array(43.73,-96.62,'Sioux_Falls'),
			array(22.7903,5.5292,'Tamanrasset'),
			array(12,123),//wrong input, satisfied initiate restrictions but wrong location
		);
		for ($i=0; $i <5; $i++) { 
			$Spot=new Leaflet_Map_Spot($location[$i][0],$location[$i][1]);
			$Spot->Inf_Match();
			$this->assertEquals($location[$i][2],$Spot->Location);//match success
		}
		$Spot=new Leaflet_Map_Spot($location[5][0],$location[5][1]);
		$Spot->Inf_Match(); 
		$this->assertEquals("Error:Can't Match Any Spot In Database",$Spot->error_log);//match failed
		unset($Spot);
	}
	public function testdbconnection(){//database and tables conncetion
		require 'solardb.php';
		$dblink_test= new mysqli($ip,$account,$pass,$solar_db);//database connection 
		$this->assertTrue(is_object($dblink_test));
		$location=array(//Testdata
			array(-15.601,-47.713,'Brasilia'),//lat,lon,location
			array(60.1389,-1.1847,'Lerwick'),
			array(-89.983,-24.799,'South_Pole'),
			array(43.73,-96.62,'Sioux_Falls'),
			array(22.7903,5.5292,'Tamanrasset')
		);
		for ($i=0; $i < 5; $i++) { //tables connection
			$Spot=new Leaflet_Map_Spot($location[$i][0],$location[$i][1]);
			$Spot->Inf_Match();
			$Spot->Weboutput_Tables();
			$this->assertTrue(!isset($Spot->error_log));
		}
	}
}
?>
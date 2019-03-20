<?php
require 'vendor/autoload.php';
use PHPUnit\Framework\TestCase;
use PHPUnit\DbUnit\TestCaseTrait;
use PHPUnit\DbUnit\DataSet\CsvDataSet;
require 'Mapspot.php';

class Leaflet_Map_SpotTest extends TestCase{
	use TestCaseTrait;//dbunit

	// only instantiate pdo once for test clean-up/fixture load
    static private $pdo = null;

    // only instantiate PHPUnit_Extensions_Database_DB_IDatabaseConnection once per test
    private $conn = null;


	public function setUp(){}
	public function tearDown(){}
	final public function getConnection()//db connection ok?
    {
    	require 'solardb.php';//use database config
        if ($this->conn === null) {
            if (self::$pdo == null) {
                self::$pdo = new PDO("mysql:host=$ip;dbname=$solar_db","$account","$pass");
            }
            $this->conn = $this->createDefaultDBConnection(self::$pdo, "$solar_db");
        }

        return $this->conn;
    }
    protected function getDataSet()
    {
        $dataSet = $this->getConnection()->createDataSet();
        return $dataSet;
    }
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
	public function testdbtablecount(){//database and tables conncetion
		$this->assertEquals(229313,$this->getConnection()->getRowCount('ghi_Brasilia'),"pre-condition");
		$this->assertEquals(659800,$this->getConnection()->getRowCount('ghi_Lerwick'),"pre-condition");
		$this->assertEquals(554316,$this->getConnection()->getRowCount('ghi_South_Pole'),"pre-condition");
		$this->assertEquals(713682,$this->getConnection()->getRowCount('ghi_Sioux_Falls'),"pre-condition");
		$this->assertEquals(87231,$this->getConnection()->getRowCount('ghi_Tamanrasset'),"pre-condition");
	}
	public function testcolumns(){//test columns and first row of data
		$location=array('Brasilia','Lerwick','South_Pole','Sioux_Falls','Tamanrasset');
		for ($i=0; $i <5; $i++) { 
			$queryTable = $this->getConnection()->createQueryTable("ghi_".$location[$i], "select * from ghi_".$location[$i]." limit 1");
			$dataSet = new CsvDataSet();
        	$dataSet->addTable("ghi_".$location[$i], "test".$location[$i].".csv");
        	$expectedTable =$dataSet->getTable("ghi_".$location[$i]);
        	$this->assertTablesEqual($expectedTable, $queryTable);
		}
	}
}
?>
/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;
import java.util.Random;




/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }
    
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("Manual Test....");
	   
/* 
 * Check basic URL formats 
 * 
 */	   
	   assertTrue(urlVal.isValid("http://www.amazon.com"));
	   assertTrue(urlVal.isValid("http://192.168.1.1"));
	   assertFalse(urlVal.isValid("http://192.168.1"));
	   assertFalse(urlVal.isValid("http://300.55.33.257"));  //<--- error1 invalid ip range?
	   assertTrue(urlVal.isValid("https://www.amazon.com"));
	   assertFalse(urlVal.isValid("httpg://www.amazon.com")); //<--- error2 invalid schemes
	   assertFalse(urlVal.isValid("skdhf://www.amazon.com"));  //<--- error
 
   }
   
   
   public void testYourFirstPartition()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   System.out.println("First Partition....");
/*
 * Partition by scheme and delimiter ie http://, https:// etc 
 * 
 */	   
	   //System.out.println("[===============First batch: scheme:============]");

	   assertTrue(urlVal.isValid("https://www.amazon.com"));
	   assertFalse(urlVal.isValid("httpg://www.amazon.com")); //<--- error2 invalid schemes
	   assertFalse(urlVal.isValid("skdhf://www.amazon.com"));  //<--- error
	   assertFalse(urlVal.isValid("http;//www.amazon.com"));
	   assertFalse(urlVal.isValid("http?//www.amazon.com"));
	   assertFalse(urlVal.isValid("://www.amazon.com"));
	   assertFalse(urlVal.isValid("//www.amazon.com"));
	   assertFalse(urlVal.isValid("www.amazon.com"));
	   
	   //System.out.println("[===============First batch: //delimiters=======]");
	   assertFalse(urlVal.isValid("http:////www.amazon.com"));
	   assertFalse(urlVal.isValid("http:/www.amazon.com"));
	   assertFalse(urlVal.isValid("http:\\www.amazon.com"));
	   assertFalse(urlVal.isValid("http:://www.amazon.com"));
	   assertFalse(urlVal.isValid("http:||www.amazon.com"));
	   assertFalse(urlVal.isValid("http:??www.amazon.com"));

   }
   
   public void testYourSecondPartition(){
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   System.out.println("Second Partition....");
/*
 * Partition input by host domain name 
 * 
 */
	   //System.out.println("[===============Second batch: //host============]");
	   assertTrue(urlVal.isValid("http://ww.amazon.com"));
	   assertFalse(urlVal.isValid("http://wwwamazoncom"));
	   assertFalse(urlVal.isValid("http://wwwama.zoncom"));
	   assertFalse(urlVal.isValid("http://w.wwama.zoncom"));
	   assertFalse(urlVal.isValid("http://wwwamazo.ncom"));
	   assertFalse(urlVal.isValid("http://wwwamazonc.omo"));
	   assertFalse(urlVal.isValid("http://wwwamazon.c0m"));
	   assertFalse(urlVal.isValid("http://wwwamazon.c"));
	   assertTrue(urlVal.isValid("http://wwwamazon.co"));
	   assertTrue(urlVal.isValid("http://wwwamazon.com"));
	   assertTrue(urlVal.isValid("http://wwwamazon.COM"));
	   assertTrue(urlVal.isValid("http://wwwamazon.edu"));
	   assertTrue(urlVal.isValid("http://wwwamazon.gov"));
	   assertTrue(urlVal.isValid("http://wwwamazon.ng"));  //<--error3? valid domains
	   assertTrue(urlVal.isValid("http://wwwamazon.nz"));   //<--error
	   assertTrue(urlVal.isValid("http://wwwamazon.ca"));
	   
   }
   
   
   public void testIsValid()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   Random rand = new Random();
	   
	   int maxVal = 0, minVal = 0;

	   //int  n = rand.nextInt(maxVal) + minVal;
	   int portN;
	   
	   for(int i = 0;i<10000;i++)
	   {
		   
//1) do domain extentions: .com, .edu etc
// make sure all entries are passing 
		   
		   //System.out.println("[== 1) do domain extentions: .com, .edu etc ==============]");
		   StringBuffer extBuffer = new StringBuffer("http://www.google");		   
		   int extpos =0;
		   
		   maxVal = testUrlExt.length - 1 ;
		   minVal = 0;
		   
		   extpos = minVal + rand.nextInt((maxVal - minVal) + 1);
		   extBuffer.append("." + testUrlExt[extpos].item);
				   
		   if (testUrlExt[extpos].valid){
			   if(!urlVal.isValid(extBuffer.toString()))
				   System.out.println("ERROR: This should be a valid URL[ " + extBuffer + " ]");
			   }
		   else{ 
			   if(urlVal.isValid(extBuffer.toString()))
				   System.out.println("ERROR: This should NOT be a valid URL[ " + extBuffer + " ]");
			   }
		   
//2) do IP address versions 0.0.0.0, -1.2.3.2.1 etc
		   //System.out.println("[== 2) do IP address versions 0.0.0.0, -1.2.3.2.1 etc ==========]");
		   StringBuffer ipBuffer = new StringBuffer("http://");
		   int a, b, c, d;
		   
		   maxVal = 999;
		   minVal = 0;
		   
		   a = minVal + rand.nextInt((maxVal - minVal) + 1);
		   b = minVal + rand.nextInt((maxVal - minVal) + 1);
		   c = minVal + rand.nextInt((maxVal - minVal) + 1);
		   d = minVal + rand.nextInt((maxVal - minVal) + 1);
		   ipBuffer.append(a + "." + b + "." + c + "." + d);
		   
		   
		   if ( (a < 256) && (b < 256) && (c < 256) && (d < 256)){
			   if(!urlVal.isValid(ipBuffer.toString()))
				   System.out.println("ERROR: This should be a valid URL[ " + ipBuffer + " ]"); 
			   }
		   else {
			   if(urlVal.isValid(ipBuffer.toString()))
				   System.out.println("ERROR: This should NOT be a valid URL[ " + ipBuffer + " ]");
			   //assertFalse(urlVal.isValid(ipBuffer.toString()));  //<---error1, invalid IPs
		     }


//3) do scheme variations https, http, ftp, etc
		   //System.out.println("[== 3) do scheme variations https, http, ftp, etc ==============]");
		   StringBuffer schemeBuffer = new StringBuffer("www.google.com");		   
		   int pos =0;
		   
		   maxVal = testUrlScheme.length - 1 ;
		   minVal = 0;
		   
		   pos = minVal + rand.nextInt((maxVal - minVal) + 1);
		   schemeBuffer.insert(0,testUrlScheme[pos].item);
				   
		   if (testUrlScheme[pos].valid){
			   if(!urlVal.isValid(schemeBuffer.toString()))
				   System.out.println("ERROR: This should be a valid URL[ " + schemeBuffer + " ]");
			   }
		   else{ 
			   if(urlVal.isValid(schemeBuffer.toString()))
				   System.out.println("ERROR: This should NOT be a valid URL[ " + schemeBuffer + " ]");
			   }
			   		   
		   
		   
//4) do port variations 0, 4345, 242 etc
		   //System.out.println("[== 4) do port variations 0, 4345, 242 etc: ports ==============]");
		   StringBuffer portBuffer = new StringBuffer("http://www.google.com:");
		   
		   maxVal = 999999;
		   minVal = -256;
		   //randomNum = minimum + rand.nextInt((maximum - minimum) + 1);
		   //REF: http://stackoverflow.com/questions/363681/generating-random-integers-in-a-specific-range
		   
		   portN = minVal + rand.nextInt((maxVal - minVal) + 1);
		   portBuffer.append(portN);
		   
		   if (portN >= 0 && portN <= 65535){
			   if(!urlVal.isValid(portBuffer.toString()))
				   System.out.println("ERROR: This should be a valid URL[ " + portBuffer + " ]");
			   }
		   else{ 
			   if(urlVal.isValid(portBuffer.toString()))
				   System.out.println("ERROR: This should NOT be a valid URL[ " + portBuffer + " ]");
			   }
   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   /*
	    * 
	    * The components of the URL are combined and delimited as follows:
	      1) scheme:
	      2) //host
	      3) :port
	      4) /path
	      5) ?query
	    * 
	    * 
	    */
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   System.out.println("Other Unit Test....");
	   
	   System.out.println("[===============First batch: scheme:============]");
	   assertTrue(urlVal.isValid("http://www.amazon.com"));
	   assertTrue(urlVal.isValid("http://192.168.1.1"));
	   assertFalse(urlVal.isValid("http://192.168.1"));
	   assertFalse(urlVal.isValid("http://900.55.33.257"));
	   assertFalse(urlVal.isValid("http://300.55.33.257.00.98.00.90"));
	   assertTrue(urlVal.isValid("https://www.amazon.com"));
	   assertFalse(urlVal.isValid("httpg://www.amazon.com")); //<--- error2 invalid schemes
	   assertFalse(urlVal.isValid("skdhf://www.amazon.com"));  //<--- error
	   assertFalse(urlVal.isValid("http;//www.amazon.com"));
	   assertFalse(urlVal.isValid("http?//www.amazon.com"));
	   assertFalse(urlVal.isValid("://www.amazon.com"));
	   assertFalse(urlVal.isValid("//www.amazon.com"));
	   assertFalse(urlVal.isValid("www.amazon.com"));
	   
	   System.out.println("[===============First batch: //delimiters=======]");
	   assertFalse(urlVal.isValid("http:////www.amazon.com"));
	   assertFalse(urlVal.isValid("http:/www.amazon.com"));
	   assertFalse(urlVal.isValid("http:\\www.amazon.com"));
	   assertFalse(urlVal.isValid("http:://www.amazon.com"));
	   assertFalse(urlVal.isValid("http:||www.amazon.com"));
	   assertFalse(urlVal.isValid("http:??www.amazon.com"));
	   
	   
	   System.out.println("[===============Second batch: //host============]");
	   assertTrue(urlVal.isValid("http://ww.amazon.com"));
	   assertFalse(urlVal.isValid("http://wwwamazoncom"));
	   assertFalse(urlVal.isValid("http://wwwama.zoncom"));
	   assertFalse(urlVal.isValid("http://w.wwama.zoncom"));
	   assertFalse(urlVal.isValid("http://wwwamazo.ncom"));
	   assertFalse(urlVal.isValid("http://wwwamazonc.omo"));
	   assertFalse(urlVal.isValid("http://wwwamazon.c0m"));
	   assertFalse(urlVal.isValid("http://wwwamazon.c"));
	   assertTrue(urlVal.isValid("http://wwwamazon.co"));
	   assertTrue(urlVal.isValid("http://wwwamazon.com"));
	   assertTrue(urlVal.isValid("http://wwwamazon.COM"));
	   assertTrue(urlVal.isValid("http://wwwamazon.edu"));
	   assertTrue(urlVal.isValid("http://wwwamazon.gov"));
	   assertTrue(urlVal.isValid("http://wwwamazon.ng"));  //<--error3? valid domains
	   assertTrue(urlVal.isValid("http://wwwamazon.nz"));   //<--error
	   assertTrue(urlVal.isValid("http://wwwamazon.ca"));
	   
	   
	   System.out.println("[===============Third batch: ports==============]");
	   assertTrue(urlVal.isValid("http://www.amazon.com:80"));
	   assertTrue(urlVal.isValid("http://www.amazon.com:80/"));
	   assertFalse(urlVal.isValid("http://www.amazon.com:80\\"));
	   assertFalse(urlVal.isValid("http://www.amazon.com:"));
	   assertTrue(urlVal.isValid("http://www.amazon.com:0"));
	   assertFalse(urlVal.isValid("http://www.amazon.com:80000000000"));
	   assertFalse(urlVal.isValid("http://www.amazon.com:8o"));
	   assertFalse(urlVal.isValid("http://www.amazon.com:ab"));
	   assertFalse(urlVal.isValid("http://www.amazon.com:-80"));
	   
	   
	   
	   
	   System.out.println("[===============Fourth batch: /paths==============]");
	   assertTrue(urlVal.isValid("http://www.amazon.com/"));
	   assertTrue(urlVal.isValid("http://www.amazon.com//"));
	   assertFalse(urlVal.isValid("http://www.amazon.com\\"));
	   assertFalse(urlVal.isValid("http://www.amazon.com\\\\"));
	   assertFalse(urlVal.isValid("http://www.amazon.com///"));
	   assertFalse(urlVal.isValid("http://www.amazon.com:ab"));
	   assertFalse(urlVal.isValid("http://www.amazon.com:-80"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/sdgfsgvscscdf"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/sdg.fsgv.scsc.df"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/sdgf/sgvscs/cdf/"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/sdgf/$"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/sdgf/*"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/sdgf/%"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/sdgf/&"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/sdgf/^"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/sdgf/( "));
	   assertTrue(urlVal.isValid("http://www.amazon.com/sdgf/)"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/sdgf/?"));

	   
	   System.out.println("[===============Fifth batch: queries==============]");
	   assertTrue(urlVal.isValid("http://www.amazon.com/"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/?"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/werwe?"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/werwe?hey"));
	   assertTrue(urlVal.isValid("http://www.amazon.com/werwe?hey="));
	   assertTrue(urlVal.isValid("http://www.amazon.com:80/werwe?hey=nothing")); //<--error4 this should work
	   assertTrue(urlVal.isValid("http://www.amazon.com:80/werwe?action=view"));

   }

   ResultPair[] testUrlScheme = {
		   					new ResultPair("http://", true),
						    new ResultPair("ftp://", true),
						    new ResultPair("h3t://", true),
						    new ResultPair("3ht://", false),
						    new ResultPair("http:/", false),
						    new ResultPair("http:", false),
						    new ResultPair("http/", false),
						    new ResultPair("://", false),
						    new ResultPair("xyz://", false),
						    new ResultPair("averylongstring://", false),
						    new ResultPair("*(&(*^://", false),
						    new ResultPair("32434123://", false),
						    new ResultPair("HTTP://", true),
						    new ResultPair("", true)};

ResultPair[] testUrlExt  = {
							new ResultPair("aero",   true),
							new ResultPair("asia",   true),
							new ResultPair("biz",    true),
							new ResultPair("cat",    true),
							new ResultPair("com",    true),
							new ResultPair("coop",   true),
							new ResultPair("info",   true),
							new ResultPair("jobs",   true),
							new ResultPair("mobi",   true),
							new ResultPair("museum", true),
							new ResultPair("name",   true),
							new ResultPair("net",    true),
							new ResultPair("org",    true),
							new ResultPair("pro",    true),
							new ResultPair("tel",    true),
							new ResultPair("travel", true),
							new ResultPair("gov",    true),
							new ResultPair("edu",    true),
							new ResultPair("mil",    true),
							new ResultPair("int",    true), 
							new ResultPair("ac",     true),
							new ResultPair("ad",     true),
							new ResultPair("ae",     true),
							new ResultPair("af",     true),
							new ResultPair("ag",     true),
							new ResultPair("ai",     true),
							new ResultPair("al",     true),
							new ResultPair("am",     true),
							new ResultPair("an",     true),
							new ResultPair("ao",     true),
							new ResultPair("aq",     true),
							new ResultPair("ar",     true),
							new ResultPair("as",     true),
							new ResultPair("at",     true),
							new ResultPair("au",     true),
							new ResultPair("aw",     true),
							new ResultPair("ax",     true),
							new ResultPair("az",     true),
							new ResultPair("ba",     true),
							new ResultPair("bb",     true),
							new ResultPair("bd",     true),
							new ResultPair("be",     true),
							new ResultPair("bf",     true),
							new ResultPair("bg",     true),
							new ResultPair("bh",     true),
							new ResultPair("bi",     true),
							new ResultPair("bj",     true),
							new ResultPair("bm",     true),
							new ResultPair("bn",     true),
							new ResultPair("bo",     true),
							new ResultPair("br",     true),
							new ResultPair("bs",     true),
							new ResultPair("bt",     true),
							new ResultPair("bv",     true),
							new ResultPair("bw",     true),
							new ResultPair("by",     true),
							new ResultPair("bz",     true),
							new ResultPair("ca",     true),
							new ResultPair("cc",     true),
							new ResultPair("cd",     true),
							new ResultPair("cf",     true),
							new ResultPair("cg",     true),
							new ResultPair("ch",     true),
							new ResultPair("ci",     true),
							new ResultPair("ck",     true),
							new ResultPair("cl",     true),
							new ResultPair("cm",     true),
							new ResultPair("cn",     true),
							new ResultPair("co",     true),
							new ResultPair("cr",     true),
							new ResultPair("cu",     true),
							new ResultPair("cv",     true),
							new ResultPair("cx",     true),
							new ResultPair("cy",     true),
							new ResultPair("cz",     true),
							new ResultPair("de",     true),
							new ResultPair("dj",     true),
							new ResultPair("dk",     true),
							new ResultPair("dm",     true),
							new ResultPair("do",     true),
							new ResultPair("dz",     true),
							new ResultPair("ec",     true),
							new ResultPair("ee",     true),
							new ResultPair("eg",     true),
							new ResultPair("er",     true),
							new ResultPair("es",     true),
							new ResultPair("et",     true),
							new ResultPair("eu",     true),
							new ResultPair("fi",     true),
							new ResultPair("fj",     true),
							new ResultPair("fk",     true),
							new ResultPair("fm",     true),
							new ResultPair("fo",     true),
							new ResultPair("fr",     true),
							new ResultPair("ga",     true),
							new ResultPair("gb",     true),
							new ResultPair("gd",     true),
							new ResultPair("ge",     true),
							new ResultPair("gf",     true),
							new ResultPair("gg",     true),
							new ResultPair("gh",     true),
							new ResultPair("gi",     true),
							new ResultPair("gl",     true),
							new ResultPair("gm",     true),
							new ResultPair("gn",     true),
							new ResultPair("gp",     true),
							new ResultPair("gq",     true),
							new ResultPair("gr",     true),
							new ResultPair("gs",     true),
							new ResultPair("gt",     true),
							new ResultPair("gu",     true),
							new ResultPair("gw",     true),
							new ResultPair("gy",     true),
							new ResultPair("hk",     true),
							new ResultPair("hm",     true),
							new ResultPair("hn",     true),
							new ResultPair("hr",     true),
							new ResultPair("ht",     true),
							new ResultPair("hu",     true),
							new ResultPair("id",     true),
							new ResultPair("ie",     true),
							new ResultPair("il",     true),
							new ResultPair("im",     true),
							new ResultPair("in",     true),
							new ResultPair("io",     true),
							new ResultPair("iq",     true),
							new ResultPair("ir",     true),
							new ResultPair("is",     true),
							new ResultPair("it",     true),
							new ResultPair("je",     true),
							new ResultPair("jm",     true),
							new ResultPair("jo",     true),
							new ResultPair("jp",     true),
							new ResultPair("ke",     true),
							new ResultPair("kg",     true),
							new ResultPair("kh",     true),
							new ResultPair("ki",     true),
							new ResultPair("km",     true),
							new ResultPair("kn",     true),
							new ResultPair("kp",     true),
							new ResultPair("kr",     true),
							new ResultPair("kw",     true),
							new ResultPair("ky",     true),
							new ResultPair("kz",     true),
							new ResultPair("la",     true),
							new ResultPair("lb",     true),
							new ResultPair("lc",     true),
							new ResultPair("li",     true),
							new ResultPair("lk",     true),
							new ResultPair("lr",     true),
							new ResultPair("ls",     true),
							new ResultPair("lt",     true),
							new ResultPair("lu",     true),
							new ResultPair("lv",     true),
							new ResultPair("ly",     true),
							new ResultPair("ma",     true),
							new ResultPair("mc",     true),
							new ResultPair("md",     true),
							new ResultPair("me",     true),
							new ResultPair("mg",     true),
							new ResultPair("mh",     true),
							new ResultPair("mk",     true),
							new ResultPair("ml",     true),
							new ResultPair("mm",     true),
							new ResultPair("mn",     true),
							new ResultPair("mo",     true),
							new ResultPair("mp",     true),
							new ResultPair("mq",     true),
							new ResultPair("mr",     true),
							new ResultPair("ms",     true),
							new ResultPair("mt",     true),
							new ResultPair("mu",     true),
							new ResultPair("mv",     true),
							new ResultPair("mw",     true),
							new ResultPair("mx",     true),
							new ResultPair("my",     true),
							new ResultPair("mz",     true),
							new ResultPair("na",     true),
							new ResultPair("nc",     true),
							new ResultPair("ne",     true),
							new ResultPair("nf",     true),
							new ResultPair("ng",     true),
							new ResultPair("ni",     true),
							new ResultPair("nl",     true),
							new ResultPair("no",     true),
							new ResultPair("np",     true),
							new ResultPair("nr",     true),
							new ResultPair("nu",     true),
							new ResultPair("nz",     true),
							new ResultPair("om",     true),
							new ResultPair("pa",     true),
							new ResultPair("pe",     true),
							new ResultPair("pf",     true),
							new ResultPair("pg",     true),
							new ResultPair("ph",     true),
							new ResultPair("pk",     true),
							new ResultPair("pl",     true),
							new ResultPair("pm",     true),
							new ResultPair("pn",     true),
							new ResultPair("pr",     true),
							new ResultPair("ps",     true),
							new ResultPair("pt",     true),
							new ResultPair("pw",     true),
							new ResultPair("py",     true),
							new ResultPair("qa",     true),
							new ResultPair("re",     true),
							new ResultPair("ro",     true),
							new ResultPair("rs",     true),
							new ResultPair("ru",     true),
							new ResultPair("rw",     true),
							new ResultPair("sa",     true),
							new ResultPair("sb",     true),
							new ResultPair("sc",     true),
							new ResultPair("sd",     true),
							new ResultPair("se",     true),
							new ResultPair("sg",     true),
							new ResultPair("sh",     true),
							new ResultPair("si",     true),
							new ResultPair("sj",     true),
							new ResultPair("sk",     true),
							new ResultPair("sl",     true),
							new ResultPair("sm",     true),
							new ResultPair("sn",     true),
							new ResultPair("so",     true),
							new ResultPair("sr",     true),
							new ResultPair("st",     true),
							new ResultPair("su",     true),
							new ResultPair("sv",     true),
							new ResultPair("sy",     true),
							new ResultPair("sz",     true),
							new ResultPair("tc",     true),
							new ResultPair("td",     true),
							new ResultPair("tf",     true),
							new ResultPair("tg",     true),
							new ResultPair("th",     true),
							new ResultPair("tj",     true),
							new ResultPair("tk",     true),
							new ResultPair("tl",     true),
							new ResultPair("tm",     true),
							new ResultPair("tn",     true),
							new ResultPair("to",     true),
							new ResultPair("tp",     true),
							new ResultPair("tr",     true),
							new ResultPair("tt",     true),
							new ResultPair("tv",     true),
							new ResultPair("tw",     true),
							new ResultPair("tz",     true),
							new ResultPair("ua",     true),
							new ResultPair("ug",     true),
							new ResultPair("uk",     true),
							new ResultPair("um",     true),
							new ResultPair("us",     true),
							new ResultPair("uy",     true),
							new ResultPair("uz",     true),
							new ResultPair("va",     true),
							new ResultPair("vc",     true),
							new ResultPair("ve",     true),
							new ResultPair("vg",     true),
							new ResultPair("vi",     true),
							new ResultPair("vn",     true),
							new ResultPair("vu",     true),
							new ResultPair("wf",     true),
							new ResultPair("ws",     true),
							new ResultPair("ye",     true),
							new ResultPair("yt",     true),
							new ResultPair("yu",     true),
							new ResultPair("za",     true),
							new ResultPair("zm",     true),
							new ResultPair("zw",     true)		
	  };
}

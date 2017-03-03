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
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   
	   
   }
   
   //partitioning by scheme input
   public void testYourFirstPartition()
   {
	   System.out.println("\nBegin Partionioning Testing by Scheme Input\n");
	   
	   String[] testTrueInput = {"", "http://", "ftp://", "h3t://"};
	   UrlValidator trueScheme = new UrlValidator(testTrueInput, 0);
	   for(int i = 0, j = 0; i < testTrueInput.length; i++, j++){
		   String currentString = testTrueInput[i];
		   System.out.print("Testing scheme input: " + currentString);
		   boolean evaluation = trueScheme.isValidScheme(currentString);
		   if(evaluation == false && i == j) System.out.println("\nFAIL\n");
		   else System.out.println("\nPASS\n");
	   }
	   
	   String[] testFalseInput = {"3ht://", "http:", "http:/", "http/", "://"}; 
	   UrlValidator falseScheme = new UrlValidator(testFalseInput, 0);   
	   for(int i = 0, j = 0; i < testFalseInput.length; i++, j++){
		   String currentString = testFalseInput[i];
		   System.out.print("Testing scheme input: " + currentString);
		   boolean evaluation = falseScheme.isValidScheme(currentString);
		   if(evaluation == true && i == j) System.out.println("\nFAIL\n");
		   else System.out.println("\nPASS\n");
	   } 
	   
	   System.out.println("End Partionioning Testing by Scheme Input\n");
   }
      
   //partitioning by authority input
   public void testYourSecondPartition(){
	   System.out.println("\nBegin Partionioning Testing by Authority Input\n");
	   
	   String[] testTrueInput = {"www.google.com", "go.com", "go.au", "255.com", "0.0.0.0", "255.255.255.255"};
	   UrlValidator trueAuthority = new UrlValidator(testTrueInput, 0);
	   for(int i = 0, j = 0; i < testTrueInput.length; i++, j++){
		   String currentString = testTrueInput[i];
		   System.out.print("Testing authority input: " + currentString);
		   boolean evaluation = trueAuthority.isValidAuthority(currentString);
		   if(evaluation == false && i == j) System.out.println("\nFAIL\n");
		   else System.out.println("\nPASS\n");
	   }
	   	   
	   String[] testFalseInput = {"", "go.a", "go.a1a", "go.1aa", "aaa.", "256.256.256.256", "999.999.999.999",
			   "9999.999.999.999", "1.2.3.4.5", "1.2.3", ".1.2.3.4"};
	   UrlValidator falseAuthority = new UrlValidator(testFalseInput, 0);
	   for(int i = 0, j = 0; i < testFalseInput.length; i++, j++){
		   String currentString = testFalseInput[i];
		   System.out.print("Testing authority input: " + currentString);
		   boolean evaluation = falseAuthority.isValidAuthority(currentString);
		   if(evaluation == true && i == j) System.out.println("\nFAIL\n");
		   else System.out.println("\nPASS\n");
	   }
	   
	   System.out.println("End Partionioning Testing by Authority Input\n");
   }
   
   //partitioning by port input
   public void testYourThirdPartition(){
	   System.out.println("\nBegin Partionioning Testing by Port Input\n");
	   
	   String[] testTrueInput = {"www.google.com", "www.google.com:0", "www.google.com:80", "www.google.com:800",
			   "www.google.com:8000", "www.google.com:65535", "www.google.com:65636"};
	   UrlValidator truePort = new UrlValidator(testTrueInput, 0);
	   for(int i = 0, j = 0; i < testTrueInput.length; i++, j++){
		   String currentString = testTrueInput[i];
		   System.out.print("Testing port input: " + currentString);
		   boolean evaluation = truePort.isValidAuthority(currentString);
		   if(evaluation == false && i == j) System.out.println("\nFAIL\n");
		   else System.out.println("\nPASS\n");
	   }
	   
	   String[] testFalseInput = {"www.google.com:-1", "www.google.com:65a"};
	   UrlValidator falsePort = new UrlValidator(testFalseInput, 0);	   
	   for(int i = 0, j = 0; i < testFalseInput.length; i++, j++){
		   String currentString = testFalseInput[i];
		   System.out.print("Testing port input: " + currentString);
		   boolean evaluation = falsePort.isValidAuthority(currentString);
		   if(evaluation == true && i == j) System.out.println("\nFAIL\n");
		   else System.out.println("\nPASS\n");
	   }
	   
	   System.out.println("End Partionioning Testing by Port Input\n");
   }
   
   //partitioning by path input
   public void testYourFourthPartition(){
	   System.out.println("\nBegin Partionioning Testing by Path Input\n");
	   
	   String[] testTrueInput = {"", "/", "/test1", "/t123", "/$23", "/test1/", "/test1/file"};	   
	   UrlValidator truePath = new UrlValidator(testTrueInput, 0);
	   for(int i = 0, j = 0; i < testTrueInput.length; i++, j++){
		   String currentString = testTrueInput[i];
		   System.out.print("Testing path input: " + currentString);
		   boolean evaluation = truePath.isValidPath(currentString);
		   if(evaluation == false && i == j) System.out.println("\nFAIL\n");
		   else System.out.println("\nPASS\n");
	   }
	   
	   String[] testFalseInput = {"/..", "/..//file", "/test1//file"};	   
	   UrlValidator falsePath = new UrlValidator(testFalseInput, 0);
	   for(int i = 0, j = 0; i < testFalseInput.length; i++, j++){
		   String currentString = testFalseInput[i];
		   System.out.print("Testing path input: " + currentString);
		   boolean evaluation = falsePath.isValidPath(currentString);
		   if(evaluation == true && i == j) System.out.println("\nFAIL\n");
		   else System.out.println("\nPASS\n");
	   }	   

	   System.out.println("End Partionioning Testing by Path Input\n");
   }
   
   //partitioning by query input
   public void testYourFifthPartition(){
	   System.out.println("\nBegin Partionioning Testing by Query Input\n");
	   
	   String[] testInput = {"", "?action=view", "?action=edit&mode=up"};
	   UrlValidator queryEvaluation = new UrlValidator(testInput, 0);
	   for(int i = 0, j = 0; i < testInput.length; i++, j++){
		   String currentQuery = testInput[i];
		   System.out.print("Testing query input: " + currentQuery);
		   boolean evaluation = queryEvaluation.isValidQuery(currentQuery);			
		   if(evaluation == false && i == j) System.out.println("\nFAIL\n");
		   else System.out.println("\nPASS\n");
	   }
	   
	   System.out.println("End Partionioning Testing by Query Input\n");
   }
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}

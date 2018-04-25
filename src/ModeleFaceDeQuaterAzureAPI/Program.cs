using System;
using System.Collections.Generic;
using System.IO;
using System.Net.Http;
using System.Net.Http.Formatting;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;

using Newtonsoft.Json;


namespace ModeleFaceDeQuaterAzureAPI
{

    class Program
    {
        static int ResultModel;
        static string[] argsQuater = new string[4];

        static int Main(string[] args)
        {
            if (args.Length == 4)
            {
                argsQuater = args;
                Console.WriteLine("Args0 :{0}", argsQuater[0]);
                Console.WriteLine("Args1 :{0}", argsQuater[1]);
                Console.WriteLine("Args2 :{0}", argsQuater[2]);
                Console.WriteLine("Args3 :{0}", argsQuater[3]);
            }
            else
            {
                //face 6 , 9;-65;-1260;9920
                argsQuater[0] = "9";
                argsQuater[1] = "-65";
                argsQuater[2] = "-1260";
                argsQuater[3] = "9920";

            }
            long dureeTicks = DateTime.Now.Ticks;
            double dureeSec;
            InvokeRequestResponseService().Wait();
            dureeSec = (DateTime.Now.Ticks - dureeTicks)/10000000.0;

            return ResultModel;
        }
        static async Task InvokeRequestResponseService()
        {
            using (var client = new HttpClient())
            {
                var scoreRequest = new
                {
                    Inputs = new Dictionary<string, List<Dictionary<string, string>>>() {
                        {
                            "input1",
                            // Replace columns labels with those used in your dataset
                            new List<Dictionary<string, string>>(){new Dictionary<string, string>(){
                                    {
                                        "Column 0", "-2"
                                    },
                                    {
                                        "dim1",  argsQuater[0]
                                    },
                                    {
                                        "dim2",  argsQuater[1]
                                    },
                                    {
                                        "dim3",  argsQuater[2]
                                    },
                                    {
                                        "dim4", argsQuater[3]
                                    },
                                    {
                                        "resultat", "0"
                                    }
                                }
                            }
                        },
                    },
                    GlobalParameters = new Dictionary<string, string>() { }
                };

                // Replace these values with your API key and URI found on https://services.azureml.net/
                const string apiKey = "ezWWcFPi4u3UXcxLDH8YKQdVc1SzM0dk001GtFWU3V2zD5ugVtjE/bAdVWlf73pBwQ2vDN+GtEqXhIcG6n4Iug==";
                const string apiUri = "https://ussouthcentral.services.azureml.net/workspaces/a48dbe1fb55b4c50b41677fc1568e2ce/services/f11e305ccecf4cafa8a66e370ffe7c2f/execute?api-version=2.0&format=swagger";

                client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", apiKey);
                client.BaseAddress = new Uri(apiUri);

                // WARNING: The 'await' statement below can result in a deadlock
                // if you are calling this code from the UI thread of an ASP.Net application.
                // One way to address this would be to call ConfigureAwait(false)
                // so that the execution does not attempt to resume on the original context.
                // For instance, replace code such as:
                //      result = await DoSomeTask()
                // with the following:
                //      result = await DoSomeTask().ConfigureAwait(false)

                HttpResponseMessage response = await client.PostAsJsonAsync("", scoreRequest);
                if (response.IsSuccessStatusCode)
                {
                    string resultJson = await response.Content.ReadAsStringAsync();
                    Console.WriteLine("Result: {0}", resultJson);


                    //Movie m = Newtonsoft.Json.JsonConvert.DeserializeObject<Movie>(resultJson);
                    //string name = m.Name;

                    JsonTextReader reader = new JsonTextReader(new StringReader(resultJson));
                    bool bTestResult = false;
                    string Result = "99";
                    while (reader.Read())
                    {
                        if (reader.Value != null)
                        {
                            Console.WriteLine("Token: {0}, Value: {1}", reader.TokenType, reader.Value);
                            if ((string)reader.Value == "Scored Labels")
                            {
                                bTestResult = true;
                            }
                            else
                            {
                                if (bTestResult)
                                {
                                    Result = (string)reader.Value;
                                }
                                bTestResult = false;
                            }
                        }
                        else
                        {
                            Console.WriteLine("Token: {0}", reader.TokenType);
                        }
                    }
                    //System.IO.File.WriteAllText(@"tst.txt", resultJson);
                    string path = string.Format("De\\De{0}.txt", Result);
                    //System.IO.File.WriteAllText(@"tst.txt", Result.ToString());
                    System.IO.File.WriteAllText(path, Result.ToString());

                }
                else
                {
                    Console.WriteLine(string.Format("The request failed with status code: {0}", response.StatusCode));

                    // Print the headers - they include the requert ID and the timestamp,
                    // which are useful for debugging the failure
                    Console.WriteLine(response.Headers.ToString());

                    string responseContent = await response.Content.ReadAsStringAsync();
                    Console.WriteLine(responseContent);

                    System.IO.File.WriteAllText(@"De\\erreur.txt", "Faild");

                }
                Console.WriteLine("toto");

            }

            ResultModel = 45;
        }
    }
}

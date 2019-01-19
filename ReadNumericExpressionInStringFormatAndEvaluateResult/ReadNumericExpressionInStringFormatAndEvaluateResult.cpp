#include "ReadNumericExpressionInStringFormatAndEvaluateResult.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <sstream>
#include <list>

bool evaluate(const char* expressionToBeEvaluated, int& result)
{
    bool evaluationStatus = false;
    //Coverted the raw string received as parameter to a C++ style string
    //Makes it easier to access individual characters without having to dereference
    const std::string expression = expressionToBeEvaluated;

    if(!expression.empty())
    {
        //Making this true, as invalid conditions are explicitly checked and marked
        evaluationStatus = true;
        std::list<int> numberList;
        std::list<char> operatorList;

        std::string number;
        for(int position = 0; position < expression.length(); ++position)
        {
            //Check if the current token is a valid digit
            if(isdigit(expression[position]))
            {
                //Valid digit encountered. Append it in the number string and wait for the complete number.
                //If a single digit or number is present in the expression,
                //it will be correctly appended in the 'number' variable and evaluated at the end.
                number += expression[position];
            }
            //Ignore Spaces
            else if(expression[position] == ' ')
            {
                continue;
            }
            //Another character enocuntered.
            //If the previous tokens were valid digits, 
            //'number' variable should contain all the digits of the number.
            else if(!number.empty())
            {
                //Get the complete number and store it
                numberList.push_back(atoi(number.c_str()));
                number.clear();

                //This block ensures that the number tokens are succeeded by a valid operator token.
                //Any character other than an operator is invalid here.
                if((expression[position] == '+') || (expression[position] == '-') ||
                    (expression[position] == '*') || (expression[position] == '/'))
                {
                    operatorList.push_back(expression[position]);
                }
                else
                {
                    //Invalid character encountered after a number
                    //Expression is invalid
                    evaluationStatus = false;
                    break;
                    
                }              
            }
            else if(expression[position] == '(')
            {
                //Evaluate the expression, get result and store it in 'number' variable.
                //A nested expression should always be followed by an operator or end of expression
                //Converting the result to string and storing it in 'number' variable 
                //will ensure the sanity of the expression, as the check for this is already happening in above step.

                const int startingPositionOfNestedExpression = position;

                //Check if the opening bracket is not present at the end of the expression
                if(startingPositionOfNestedExpression < (expression.length() - 1))
                {
                    //Don't consider the opening brackets in the expression length
                    int lengthOfNestedExpression = 0;
                    int counterForCheckingBrackets = 1;

                    //Search for the appropriate closing bracket in the remaining expression 
                    for(position = startingPositionOfNestedExpression + 1; position < expression.length(); ++position)
                    {
                        ++lengthOfNestedExpression;  

                        //Check if another opening bracket is encountered 
                        if(expression[position] == '(')
                        {
                            ++counterForCheckingBrackets;
                        }
                        //Check if a closing bracket is encountered
                        else if(expression[position] == ')')
                        {
                            --counterForCheckingBrackets;

                            if(0 == counterForCheckingBrackets)
                            {
                                //Don't consider the closing brackets in the expression length
                                --lengthOfNestedExpression;

                                const std::string nestedExpression = expression.substr((startingPositionOfNestedExpression + 1), 
                                                                                        (lengthOfNestedExpression));
                                int resultForNestedExpression = 0;
                                //Used recursion to evaluate nested expressions
                                if(evaluate(nestedExpression.c_str(), resultForNestedExpression))
                                {
                                    //Ther nested expression was successfully evaluated.
                                    //Covert the result into string and store in the 'number' variable
                                    std::stringstream numberStream;
                                    numberStream << resultForNestedExpression;
                                    number = numberStream.str();
                                }
                                else
                                {
                                    counterForCheckingBrackets = -1;
                                    evaluationStatus = false;
                                }

                                //Break the inner loop
                                break;
                            }

                            //Keep searching for the correct closing bracket.
                        }
                        else if(isdigit(expression[position]) || expression[position] == ' ' ||
                                (expression[position] == '+') || (expression[position] == '-') ||
                                (expression[position] == '*') || (expression[position] == '/'))
                        {
                            //Valid tokens inside the nested expression. Ignore.
                        }
                        else
                        {
                            //Invalid token encountered.
                            counterForCheckingBrackets = -1;
                            evaluationStatus = false;
                            break;
                        }
                    }

                    //Check added for breaking the outer loop
                    if(counterForCheckingBrackets != 0)
                    {
                        evaluationStatus = false;
                        break;
                    }
                }
            }
            else
            {
                //Invalid token.
                //Closing bracket encountered before an opening bracket.
                evaluationStatus = false;
                break;
            }
        }

        if(evaluationStatus)
        {
            //Make the status true, only if the remaining checks pass
            evaluationStatus = false;
            //Check for the number or evaluated result value of a nested expression present at the end OF expression
            if(!number.empty())
            {
                numberList.push_back(atoi(number.c_str()));
                number.clear();
            }

            //All the numbers and their respective operators are stored in the number and operator lists.

            if((numberList.size() - operatorList.size()) == 1)
            {
                //The size of the number list should be greater than exactly one, by the size of the operator list.

                //Evalute the final result of the expression
                while((numberList.size() >= 2) && !operatorList.empty())
                {
                    int leftOperand = numberList.front();
                    numberList.pop_front();
                    int rightOperand = numberList.front();
                    numberList.pop_front();

                    if(operatorList.front() == '+')
                    {
                        numberList.push_front(leftOperand + rightOperand);
                    }
                    else if(operatorList.front() == '-')
                    {
                        numberList.push_front(leftOperand - rightOperand);
                    }
                    else if(operatorList.front() == '*')
                    {
                        numberList.push_front(leftOperand * rightOperand);
                    }
                    else if(operatorList.front() == '/')
                    {
                        numberList.push_front(leftOperand / rightOperand);
                    }
                    else
                    {
                        //Something went wrong.
                        evaluationStatus = false;
                        break;
                    }
                    //After operation is completed, remove the operator from list, so that next operation can be performed
                    operatorList.pop_front();
                }

                //At this point, the numberList should contain only one element, the final result.
                if((numberList.size() == 1) && (operatorList.empty()))
                {
                    result = numberList.front();
                    //Final result successfully evaluated
                    evaluationStatus = true;
                }
            }
        }
    }

    return evaluationStatus;
}



// int main()
// {
//     bool evaluationStatus = false;
//     int result = 0;

//     // std::string expression = "11";
//     // std::string expression = "( 1 )";
//     // std::string expression = "11 + 33";
//     // std::string expression = "(11 + 338)";
//     // std::string expression = "(1 + 3)* 2";
//     // std::string expression = "(4 / 2) +6";
//     // std::string expression = "(4 / 2) +6 4 + (12 / (1 * 2))";
//     // const char* expression = "(4 / 2) +6 -4 + (12 / (1 * 2))";
//     // const char* expression = "((4 / 2) +6 4 (8 / (12 / 1 * 2))";
//     evaluationStatus = evaluate(expression, result);

//     std::cout << expression << std::endl << "Evaluation Status : " << evaluationStatus << std::endl;
//     if(evaluationStatus)
//     {
//         std::cout << "Result : " << result << std::endl;
//     }

//     return 0;
// }
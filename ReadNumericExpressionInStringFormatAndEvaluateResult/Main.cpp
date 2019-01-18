#include <iostream>
#include <string>
#include <list>

using namespace std;

bool evaluate(const string& expression, int& result)
{
    bool evaluationStatus = false;
    string updatedExpression = expression;

    if(!expression.empty())
    {
        evaluationStatus = true;
        list<int> numberList;
        list<char> operatorList;

        string number;
        for(int position = 0; position < expression.length(); ++position)
        {
            //Check if the current token is a valid digit
            if(isdigit(expression[position]))
            {
                //Valid digit encountered. Append it in the number string and wait for the complete number.
                number += expression[position];
            }
            else
            {
                //Ignore spaces
                if(expression[position] == ' ')
                {
                    continue;
                }
                else if(!number.empty())
                {
                    //This block ensures that the number tokens are succeeded by a valid operator token.
                    //Any character other than an operator is invalid here.

                    //Get the complete number and store it
                    numberList.push_back(stoi(number));
                    number.clear();

                    //After the number, only a valid operator should be present
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
                    

                }
            }
        }

        //Check for the last number or evaluated result value of a nested expression present at the end
        if(!number.empty())
        {
            numberList.push_back(stoi(number));
            number.clear();
        }

        if(evaluationStatus)
        {
            //The expression is valid.
            //All the numbers and their respective operators are stored in the number and operator lists.
            if((numberList.size() - operatorList.size()) == 1)
            {
                //The size of the number list should be greater than exactly one, by the size of the operator list.

                //Evalute the final result of the expression
                while((numberList.size() >= 2) || !operatorList.empty())
                {
                    int leftOperand = numberList.front();
                    numberList.pop_front();
                    int rightOperand = numberList.front();
                    numberList.pop_front();

                    if(operatorList.front() == '+')
                    {
                        result = leftOperand + rightOperand;
                        numberList.push_front(result);
                    }
                    else if(operatorList.front() == '-')
                    {
                        result = leftOperand - rightOperand;
                        numberList.push_front(result);
                    }
                    else if(operatorList.front() == '*')
                    {
                        result = leftOperand * rightOperand;
                        numberList.push_front(result);
                    }
                    else if(operatorList.front() == '/')
                    {
                        result = leftOperand / rightOperand;
                        numberList.push_front(result);
                    }
                    else
                    {
                        //Something went wrong.
                        evaluationStatus = false;
                        break;
                    }
                    operatorList.pop_front();
                }
            }
            else
            {
                evaluationStatus = false;
            }
        }
        











        // evaluationStatus = true;
        // for(int position = 0; position <= expression.length(); ++position)
        // {
        //     if(expression[position] == '(')
        //     {
        //         //First, solve all the nested expressions

        //         //Search for the position of the appropriate closing bracket 
        //         //and get the substring for the nested expression.
                
        //         //Counter for checking sanity of the brackets and finding correct closing bracket
        //         int closingBracketFlagCounter = 1;
        //         const int nestedExpressionStartingPosition = position;
                
        //         if(nestedExpressionStartingPosition < (expression.length() - 1))
        //         {
        //             int nestedExpressionLength = 1;
        //             for(int nestedExpressionPosition = nestedExpressionStartingPosition + 1; 
        //                     nestedExpressionPosition < expression.length(); 
        //                     ++nestedExpressionPosition)
        //             {
        //                 ++nestedExpressionLength;   
        //                 if(expression[nestedExpressionPosition] == '(')
        //                 {
        //                     ++closingBracketFlagCounter;
        //                 }
        //                 else if(expression[nestedExpressionPosition] == ')')
        //                 {
        //                     --closingBracketFlagCounter;

        //                     if(0 == closingBracketFlagCounter)
        //                     {
        //                         if(nestedExpressionLength == 2)
        //                         {
        //                             updatedExpression.replace(nestedExpressionStartingPosition, nestedExpressionLength, " ");
        //                         }
        //                         else if(nestedExpressionLength == 3)
        //                         {
        //                             if(isdigit(expression[nestedExpressionStartingPosition + 1]))
        //                             {
        //                                 int resultForNestedExpression = expression[nestedExpressionStartingPosition + 1] - '0';
        //                                 updatedExpression.replace(nestedExpressionStartingPosition, nestedExpressionLength, to_string(resultForNestedExpression));
        //                             }
        //                             else
        //                             {
        //                                 closingBracketFlagCounter = -1;
        //                                 evaluationStatus = false;
        //                                 break;
        //                             }
        //                         }
        //                         else
        //                         {
        //                             const string nestedExpression = expression.substr((nestedExpressionStartingPosition + 1), 
        //                                                                             (nestedExpressionLength - 1));
        //                             int resultForNestedExpression = 0;
        //                             if(evaluate(nestedExpression, resultForNestedExpression))
        //                             {
        //                                 updatedExpression.replace(nestedExpressionStartingPosition, nestedExpressionLength, to_string(resultForNestedExpression));
        //                             }
        //                             else
        //                             {
        //                                 closingBracketFlagCounter = -1;
        //                                 evaluationStatus = false;
        //                                 break;
        //                             }
        //                         }
        //                     }
        //                 }
        //                 else
        //                 {
        //                     //ignore
        //                 }
        //             }

        //             if(closingBracketFlagCounter != 0)
        //             {
        //                 evaluationStatus = false;
        //                 break;
        //             }
        //         }
        //     }
        // }
    }

    return evaluationStatus;
}
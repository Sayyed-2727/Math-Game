#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum EnDificulty {EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4};

enum EnOperationType {Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5};

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    EnOperationType OperationType;
    EnDificulty QuestionDificulty;
    int CorrectAnswer;
    int PlayerAnswer;
    bool AnswerResult = false;
};

struct stQuizz 
{
    stQuestion QuestionList[100];
    short QuestionNumber;
    EnDificulty QuestionsDificulty;
    EnOperationType OperationType;
    short NumberOfRightAnswer = 0;
    short NumberOfWrongAnswer = 0;
    bool IsPassed = false;
};

struct StFinalResults
{
    short NumberOfQuestions         = 0;
    EnDificulty QuestionsDificulty;
    EnOperationType OperationType;
    short NumberOfRightAnswers      = 0;
    short NumberOfWrongAnswers      = 0;
};

int HowManyQuestions()
{
    int HowManyQuestions;

    do
    {
        cout << "How Many Questions Do You Want To Answer? (maximum 100)" << endl;
        cin >> HowManyQuestions;
    } while (HowManyQuestions > 10 || HowManyQuestions < 1);
    
    return HowManyQuestions;
}

short RandomNumber(short from, short to)
{
    short RandomNumber;

    RandomNumber = rand() % (to-from+1) + from;
    return RandomNumber;
}

EnDificulty ReadUserDificulty()
{
    short UserDificulty = 0;

    do
    {
        cout << "Enter Questions Level: ([1] Easy, [2] Med, [3] Hard, [4] Mix)" << endl;
        cin >> UserDificulty;
    } while (UserDificulty > 4 || UserDificulty < 1);
    
    return (EnDificulty) UserDificulty;
}

string GenerateOperation(EnOperationType OperationType)
{
    string ArrOperationType[4] = {"+", "-", "*" , "/"};

    switch (OperationType)
    {
    case EnOperationType::Add :
        return ArrOperationType[0];
        break;
    
    case EnOperationType::Sub :
        return ArrOperationType[1];
        break;
    
    case EnOperationType::Mul :
        return ArrOperationType[2];
        break;
    
    case EnOperationType::Div :
        return ArrOperationType[3];
        break;
    
    case EnOperationType::MixOp :
    return ArrOperationType[RandomNumber(0,3)];
    }
}

EnOperationType ReadUserOperationType()
{
    short UserOperationType = 0;

    do
    {
        cout << "Enter Operation Type: ([1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix)" << endl;
        cin >> UserOperationType;
    } while (UserOperationType > 5 || UserOperationType < 1);
    
    return (EnOperationType) UserOperationType;
}

int ReadQuestionAnswer()
{
    short answer = 0;
    cin >> answer;
    return answer;
}

void ClearScreen()
{
    system("cls");
    system("color 0F");
}

EnOperationType GetRandomOperationType()
{
    int Op = RandomNumber(1,4);
    return (EnOperationType) Op;
}

int SimpleCalculator(int N1, int N2, EnOperationType OpType )
{
    switch (OpType)
    {
    case EnOperationType::Add :
        return N1 + N2;
    
    case EnOperationType::Sub :
        return N1 - N2;
    
    case EnOperationType::Mul :
        return N1 * N2;
    
    case EnOperationType::Div :
        return N1 / N2;
    default:
        return N1 + N2;
    }

}

stQuestion GenerateQuestion(EnDificulty QuestionDificulty, EnOperationType OpType)
{
    stQuestion Question;
    if (QuestionDificulty == EnDificulty::Mix)
    {
        QuestionDificulty = (EnDificulty) RandomNumber(1,3);
    }

    if (OpType == EnOperationType::MixOp)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperationType = OpType;

    switch (QuestionDificulty)
    {
    case EnDificulty::EasyLevel :
        Question.Number1 = RandomNumber(1,10);
        Question.Number2 = RandomNumber(1,10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionDificulty = QuestionDificulty;
        return Question;
        
    case EnDificulty::MedLevel :
        Question.Number1 = RandomNumber(10,50);
        Question.Number2 = RandomNumber(10,50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionDificulty = QuestionDificulty;
        return Question;

    case EnDificulty::HardLevel :
        Question.Number1 = RandomNumber(50,100);
        Question.Number2 = RandomNumber(50,100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionDificulty = QuestionDificulty;
        return Question;

    }

    return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short Question = 0; Question < Quizz.QuestionNumber ; Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsDificulty, Quizz.OperationType);
    }
}

string GetOpTypeSymbol(EnOperationType OpType)
{
    switch (OpType)
    {
    case EnOperationType::Add:
        return "+";
    case EnOperationType::Sub:
        return "-";
    case EnOperationType::Mul :
        return "x";
    case EnOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.QuestionNumber << "]" << endl << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << endl << "__________________" << endl;

}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); // Green for correct answers.
    else
    {
        system("color 4F"); // Red for incorrect answers.
        cout << "\a"; // Plays an alert sound.
    }
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;

        cout << "WrongAnswer :(" << endl;
        cout << "The Right asnwer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;

        cout << "Right answer :)" << endl;
    }

    cout << endl;

    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
    
    
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.QuestionNumber; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.IsPassed = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);

    /*
    if (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers)
        Quizz.ispass = true;

    else
        Quizz.ispass = false;
    
    */

}

string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return "Pass :)";
    else
        return "Fail :(";
}

string GetQuestionLevelText(EnDificulty Dificulty)
{
    string arrQuestionDificulty[4] = {"Easy", "Med", "Hard", "Mix"};
    return arrQuestionDificulty[Dificulty - 1];
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << endl;
    cout << "___________________________________________________" << endl << endl;
    cout << "Final Results is: " << GetFinalResultsText(Quizz.IsPassed) << endl << endl;
    cout << "___________________________________________________" << endl << endl;

    cout << "Number of Questions: " << Quizz.QuestionNumber << endl;
    cout << "Questions Level: " << GetQuestionLevelText(Quizz.QuestionsDificulty)<< endl;
    cout << "Optype: " << GetOpTypeSymbol(Quizz.OperationType) << endl;
    cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswer << endl;
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswer << endl << endl;
    cout << "_____________________________________________________________________________________";

}

StFinalResults PlayMathGame()
{
    stQuizz Quizz;
    Quizz.QuestionNumber = HowManyQuestions();
    Quizz.QuestionsDificulty = ReadUserDificulty();
    Quizz.OperationType = ReadUserOperationType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);


    PrintQuizzResults(Quizz);
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ClearScreen();
        PlayMathGame();

        cout << endl << "Do you want to play again? Y/N?";
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');
    
}

int main()
{

    srand((unsigned)time(NULL));

    StartGame();


    return 0;
}

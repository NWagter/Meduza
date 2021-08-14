#pragma once

namespace Me
{
    namespace Event
    {
        
        enum class MouseButton
        {
            RButton,
            LButton,
            MButton
        };

        enum class MouseEvent
        {
            MouseUp,
            MouseDown,
            Pressed
        };

        enum class KeyCode
        {
            A = 65,
            B = 66,
            C = 67,
            D = 68,
            E = 69,
            F = 70,
            G = 71,
            H = 72,
            I = 73,
            J = 74,
            K = 75,
            L = 76,
            M = 77,
            N = 78,
            O = 79,
            P = 80,
            Q = 81,
            R = 82,
            S = 83,
            T = 84,
            U = 85,
            V = 86,
            W = 87,
            X = 88,
            Y = 89,
            Z = 90,

            Num0 = 34,
            Num1 = 35,
            Num2 = 36,
            Num3 = 37,
            Num4 = 38,
            Num5 = 39,
            Num6 = 40,
            Num7 = 41,
            Num8 = 42,
            Num9 = 43,
            
            Space = 32,
            Enter = 13,
            Back = 8,
            Up = 38,
            Right = 39,
            Down = 40,
            Left = 37,
            Ctrl = 17,
#ifdef PLATFORM_WINDOWS
            Shift = 16,
#elif PLATFORM_LINUX
            Shift = 50,
#endif
        };

        enum class KeyState
        {
            KeyDown,
            KeyUp
        };

    }
}
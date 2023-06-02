using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct Tool
{
    public Tool (Color toolColor, Sprite toolSprite)
    {
        ToolColor = toolColor;
        ToolSprite = toolSprite;
    }

    public Color ToolColor { get; }
    public Sprite ToolSprite { get; }
}

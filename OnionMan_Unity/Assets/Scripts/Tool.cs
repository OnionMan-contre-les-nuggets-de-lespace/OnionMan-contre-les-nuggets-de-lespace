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

    public override int GetHashCode()
    {
        return this.ToString().GetHashCode();
    }

    public override bool Equals(object o)
    {
        var p = (Tool)o;
        if (p.ToolColor == this.ToolColor && p.ToolSprite == this.ToolSprite)
            return true;
        else
            return false;
    }

    public static bool operator ==(Tool a, Tool b)
    {
        Debug.Log("Color is equal :  " + (a.ToolColor == b.ToolColor).ToString());
        Debug.Log("Sprite is equal :  " + (a.ToolSprite == b.ToolSprite).ToString());

        return a.ToolColor == b.ToolColor && a.ToolSprite == b.ToolSprite;
    }
    public static bool operator !=(Tool a, Tool b)
    {
        return a.ToolColor != b.ToolColor && a.ToolSprite != b.ToolSprite;
    }
}

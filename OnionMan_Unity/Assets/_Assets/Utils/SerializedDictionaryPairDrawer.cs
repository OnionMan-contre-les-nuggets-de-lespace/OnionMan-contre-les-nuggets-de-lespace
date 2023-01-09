using UnityEngine;
using UnityEditor;

/// <summary>
/// Custom inspector dictionary
/// </summary>
namespace OnionMan.Utils
{
	[CustomPropertyDrawer(typeof(ISerializedDictionaryPair), true)]
	public class SerializedDictionaryPairDrawer: PropertyDrawer
	{
		public override float GetPropertyHeight(SerializedProperty property, GUIContent label)
		{
			return Mathf.Max(
				EditorGUI.GetPropertyHeight(property.FindPropertyRelative("Key")),
				EditorGUI.GetPropertyHeight(property.FindPropertyRelative("Value")));
		}

		public override void OnGUI(Rect rect, SerializedProperty pair, GUIContent label)
		{
			SerializedProperty key = pair.FindPropertyRelative("Key");
			SerializedProperty value = pair.FindPropertyRelative("Value");

			EditorGUI.PropertyField(
				new Rect(rect.x, rect.y-1, rect.width / 3f - 15f, rect.height),
				key, GUIContent.none, true);				
			
			EditorGUI.PropertyField(
				new Rect(rect.x + rect.width / 3f + 15, rect.y-1, rect.width / 1.5f - 15f, rect.height),
				value, GUIContent.none, true);

			EditorGUI.LabelField(
				new Rect(rect.x + rect.width / 3f - 5, rect.y-1, rect.x + rect.width / 2f + 15f, rect.height),
				"►"
			);
		}
	}
}

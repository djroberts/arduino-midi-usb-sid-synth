package com.goblin.sidvoice;


import voltage.controllers.*;
import voltage.core.*;
import voltage.core.Jack.JackType;
import voltage.sources.*;
import voltage.utility.*;
import voltage.processors.*;
import voltage.effects.*;
import java.awt.*;

//[user-imports]   Add your own imports here

import javax.sound.midi.ShortMessage;

import com.goblin.utils.*;

//[/user-imports]


public class SidVoice extends VoltageModule
//[user-inheritance]
//[/user-inheritance]
{

   public SidVoice( long moduleID, VoltageObjects voltageObjects )
   {
      super( moduleID, voltageObjects, "SidVoice", ModuleType.ModuleType_Utility, 8.2 );

      InitializeControls();


      canBeBypassed = false;
      SetSkin( "1582892bd74044948e8989576a23d04f" );
   }

void InitializeControls()
{

      attack = new VoltageSlider( "attack", "Attack", this, true, 0.0, 15, 0.5, 16 );
      AddComponent( attack );
      attack.SetWantsMouseNotifications( false );
      attack.SetPosition( 427, 12 );
      attack.SetSize( 10, 91 );
      attack.SetSkin( "Straight Black Plain" );
      attack.DisplayValueInPercent( false );

      decay = new VoltageSlider( "decay", "Decay", this, true, 0.0, 15, 0.5, 16 );
      AddComponent( decay );
      decay.SetWantsMouseNotifications( false );
      decay.SetPosition( 453, 11 );
      decay.SetSize( 10, 91 );
      decay.SetSkin( "Straight Black Plain" );
      decay.DisplayValueInPercent( false );

      sustain = new VoltageSlider( "sustain", "Sustain", this, true, 0.0, 15, 0.5, 16 );
      AddComponent( sustain );
      sustain.SetWantsMouseNotifications( false );
      sustain.SetPosition( 477, 13 );
      sustain.SetSize( 10, 91 );
      sustain.SetSkin( "Straight Black Plain" );
      sustain.DisplayValueInPercent( false );

      release = new VoltageSlider( "release", "Release", this, true, 0.0, 15, 0.5, 16 );
      AddComponent( release );
      release.SetWantsMouseNotifications( false );
      release.SetPosition( 503, 12 );
      release.SetSize( 10, 91 );
      release.SetSkin( "Straight Black Plain" );
      release.DisplayValueInPercent( false );

      midiOut = new VoltageMidiJack( "midiOut", "midiOut", this, JackType.JackType_MidiOutput );
      AddComponent( midiOut );
      midiOut.SetWantsMouseNotifications( false );
      midiOut.SetPosition( 529, 311 );
      midiOut.SetSize( 37, 37 );
      midiOut.SetSkin( "Mini MIDI Jack" );

      triangleButton = new VoltageToggle( "triangleButton", "Triangle", this, false, 0 );
      AddComponent( triangleButton );
      triangleButton.SetWantsMouseNotifications( false );
      triangleButton.SetPosition( 29, 13 );
      triangleButton.SetSize( 39, 19 );
      triangleButton.SetSkin( "Short Green" );
      triangleButton.ShowOverlay( false );
      triangleButton.SetOverlayText( "" );

      sawButton = new VoltageToggle( "sawButton", "Saw", this, false, 0 );
      AddComponent( sawButton );
      sawButton.SetWantsMouseNotifications( false );
      sawButton.SetPosition( 85, 10 );
      sawButton.SetSize( 39, 19 );
      sawButton.SetSkin( "Short Green" );
      sawButton.ShowOverlay( false );
      sawButton.SetOverlayText( "" );

      squareButton = new VoltageToggle( "squareButton", "Square", this, false, 0 );
      AddComponent( squareButton );
      squareButton.SetWantsMouseNotifications( false );
      squareButton.SetPosition( 137, 13 );
      squareButton.SetSize( 39, 19 );
      squareButton.SetSkin( "Short Green" );
      squareButton.ShowOverlay( false );
      squareButton.SetOverlayText( "" );

      noiseButton = new VoltageToggle( "noiseButton", "Noise", this, false, 0 );
      AddComponent( noiseButton );
      noiseButton.SetWantsMouseNotifications( false );
      noiseButton.SetPosition( 196, 14 );
      noiseButton.SetSize( 39, 19 );
      noiseButton.SetSkin( "Short Green" );
      noiseButton.ShowOverlay( false );
      noiseButton.SetOverlayText( "" );

      pulseWidth = new VoltageKnob( "pulseWidth", "pulseWidth", this, 0.0, 127, 64 );
      AddComponent( pulseWidth );
      pulseWidth.SetWantsMouseNotifications( false );
      pulseWidth.SetPosition( 145, 44 );
      pulseWidth.SetSize( 27, 27 );
      pulseWidth.SetSkin( "Plastic White" );
      pulseWidth.SetRange( 0.0, 127, 64, false, 128 );
      pulseWidth.SetKnobParams( 215, 145 );
      pulseWidth.DisplayValueInPercent( false );
      pulseWidth.SetKnobAdjustsRing( true );
}



   //-------------------------------------------------------------------------------
   //  public void Initialize()

      //  Initialize will get called shortly after your module's constructor runs. You can use it to
      //  do any initialization that the auto-generated code doesn't handle.
   //-------------------------------------------------------------------------------
   @Override
   public void Initialize()
   {
      //[user-Initialize]   Add your own initialization code here



      //[/user-Initialize]
   }


   //-------------------------------------------------------------------------------
   //  public void Destroy()

      //  Destroy will get called just before your module gets deleted. You can use it to perform any
      //  cleanup that's not handled automatically by Java.
   //-------------------------------------------------------------------------------
   @Override
   public void Destroy()
   {
      super.Destroy();
      //[user-Destroy]   Add your own module-getting-deleted code here



      //[/user-Destroy]
   }


   //-------------------------------------------------------------------------------
   //  public boolean Notify( VoltageComponent component, ModuleNotifications notification, double doubleValue, long longValue, int x, int y, Object object )

      //  Notify will get called when various events occur - control values changing, timers firing, etc.
   //-------------------------------------------------------------------------------
   @Override
   public boolean Notify( VoltageComponent component, ModuleNotifications notification, double doubleValue, long longValue, int x, int y, Object object )
   {
      //[user-Notify]   Add your own notification handling code between this line and the notify-close comment
      switch( notification )
      {
         case Knob_Changed:   // doubleValue is the new VoltageKnob value
         {
            if (component == pulseWidth) {
               sendShortPulseWidth();
            } else {
               sendMidi();                     
            }
         }
         break;
      
         case Slider_Changed:   // doubleValue is the new slider value
         {
            sendMidi();
         }
         break;
      
         case Button_Changed:   // doubleValue is the new button/toggle button value
         {
            sendMidi();
         }
         break;
      
         case Switch_Changed:   // doubleValue is the new switch value
         {
         }
         break;
      
         case Jack_Connected:   // longValue is the new cable ID
         {
         }
         break;
      
         case Jack_Disconnected:   // All cables have been disconnected from this jack
         {
         }
         break;
      
         case GUI_Update_Timer:   // Called every 50ms (by default) if turned on
         {
         }
         break;
      
         case Object_MouseMove:   // called when mouse is over an object that receives mouse notifications. 'object' parameter is a VoltageMouseKeyFlags object.
         {
         }
         break;
      
         case Object_MouseLeave:  // called when mouse leaves an object that receives mouse notifications. 'object' parameter is a VoltageMouseKeyFlags object.
         {
         }
         break;
      
         case Object_LeftButtonDown:   // called when user left-clicks on an object that receives mouse notifications. 'object' parameter is a VoltageMouseKeyFlags object.
         {
         }
         break;
      
         case Object_LeftButtonUp:   // called when user releases left mouse button on an object that receives mouse notifications. 'object' parameter is a VoltageMouseKeyFlags object.
         {
         }
         break;
      
         case Object_RightButtonDown:   // called when user releases right mouse button on an object that receives mouse notifications. 'object' parameter is a VoltageMouseKeyFlags object.
         {
         }
         break;
      
         case Object_RightButtonUp:   // called when user right-clicks on an object that receives mouse notifications
         {
         }
         break;
      
         case Object_LeftButtonDoubleClick: // called when user left-button double-clicks on an object that receives mouse notifications
         {
         }
         break;
      
         // Less common notifications:
      
         case Named_Timer:   // object contains a String with the name of the timer that has fired
         {
         }
         break;
      
         case Canvas_Painting:   // About to paint canvas.  object is a java.awt.Rectangle with painting boundaries
         {
         }
         break;
      
         case Canvas_Painted:   // Canvas painting is complete
         {
         }
         break;
      
         case Control_DragStart:    // A user has started dragging on a control that has been marked as draggable
         {
         }
         break;
      
         case Control_DragOn:       // This control has been dragged over during a drag operation. object contains the dragged object
         {
         }
         break;
      
         case Control_DragOff:      // This control has been dragged over during a drag operation. object contains the dragged object
         {
         }
         break;
      
         case Control_DragEnd:      // A user has ended their drag on a control that has been marked as draggable
         {
         }
         break;
      
         case Label_Changed:        // The text of an editable text control has changed
         {
         }
         break;
      
         case SoundPlayback_Start:   // A sound has begun playback
         {
            sendMidi();

         }
         break;
      
         case SoundPlayback_End:     // A sound has ended playback
         {
         }
         break;
      
         case Scrollbar_Position:    // longValue is the new scrollbar position
         {
         }
         break;
      
         case PolyVoices_Changed:    // longValue is the new number of poly voices
         {
         }
         break;
      
         case File_Dropped:     // 'object' is a String containing the file path
         {
         }
         break;
      
         case Preset_Loading_Start:   // called when preset loading begins
         {
         }
         break;
      
         case Preset_Loading_Finish:  // called when preset loading finishes
         {
         }
         break;
      
         case Variation_Loading_Start:    // sent when a variation is about to load
         {
         }
         break;
      
         case Variation_Loading_Finish:   // sent when a variation has just finished loading
         {
         }
         break;
      
         case Tempo_Changed:     // doubleValue is the new tempo
         {
         }
         break;
      
         case Randomized:     // called when the module's controls get randomized
         {
         }
         break;
      
         case VariationListChanged:   // sent when a variation gets added, deleted, or renamed, or the variations list gets reordered
         {
         }
         break;
      
         case Key_Press:     // sent when module has keyboard focus and a key is pressed; object is a VoltageKeyPressInfo object
         {
         }
         break;
      
         case Reset:    // sent when the module has been reset to default settings
         {
         }
         break;
      
         case Keyboard_NoteOn:   // sent when a note has been pressed on a VoltageKeyboard object. longValue is the note value ( 0-127 )
         {
         }
         break;
      
         case Keyboard_NoteOff:   // sent when a note has been released on a VoltageKeyboard object. longValue is the note value ( 0-127 )
         {
         }
         break;
      
         case Curve_Changed:   // sent when user has edited a curve's value. 'object' will be a VoltageCurve.CurveChangeNotification object.
         {
         }
         break;
      }



      return false;
      //[/user-Notify]
   }


   //-------------------------------------------------------------------------------
   //  public void ProcessSample()

      //  ProcessSample is called once per sample. Usually it's where you read
      //  from input jacks, process audio, and write it to your output jacks.
      //  Since ProcesssSample gets called 48,000 times per second, offload CPU-intensive operations
      //  to other threads when possible and avoid calling native functions.
   //-------------------------------------------------------------------------------
   @Override
   public void ProcessSample()
   {
      //[user-ProcessSample]   Add your own process-sampling code here



      //[/user-ProcessSample]
   }


   //-------------------------------------------------------------------------------
   //  public String GetTooltipText( VoltageComponent component )

      //  Gets called when a tooltip is about to display for a control. Override it if
      //  you want to change what the tooltip displays - if you want a knob to work in logarithmic fashion,
      //  for instance, you can translate the knob's current value to a log-based string and display it here.
   //-------------------------------------------------------------------------------
   @Override
   public String GetTooltipText( VoltageComponent component )
   {
      //[user-GetTooltipText]   Add your own code here



      return super.GetTooltipText( component );
      //[/user-GetTooltipText]
   }


   //-------------------------------------------------------------------------------
   //  public void EditComponentValue( VoltageComponent component, double newValue, String newText )

      //  Gets called after a user clicks on a tooltip and types in a new value for a control. Override this if
      //  you've changed the default tooltip display (translating a linear value to logarithmic, for instance)
      //  in GetTooltipText().
   //-------------------------------------------------------------------------------
   @Override
   public void EditComponentValue( VoltageComponent component, double newValue, String newText )
   {
      //[user-EditComponentValue]   Add your own code here



      //[/user-EditComponentValue]
      super.EditComponentValue( component, newValue, newText );
   }


   //-------------------------------------------------------------------------------
   //  public void OnUndoRedo( String undoType, double newValue, Object optionalObject )

      //  If you've created custom undo events via calls to CreateUndoEvent, you'll need to
      //  process them in this function when they get triggered by undo/redo actions.
   //-------------------------------------------------------------------------------
   @Override
   public void OnUndoRedo( String undoType, double newValue, Object optionalObject )
   {
      //[user-OnUndoRedo]   Add your own code here



      //[/user-OnUndoRedo]
   }


   //-------------------------------------------------------------------------------
   //  public byte[] GetStateInformation()

      //  Gets called when the module's state gets saved, typically when the user saves a preset with
      //  this module in it. Voltage Modular will automatically save the states of knobs, sliders, etc.,
      //  but if you have any custom state information you need to save, return it from this function.
   //-------------------------------------------------------------------------------
   @Override
   public byte[] GetStateInformation()
   {
      //[user-GetStateInformation]   Add your own code here



      return null;
      //[/user-GetStateInformation]
   }


   //-------------------------------------------------------------------------------
   //  public void SetStateInformation(byte[] stateInfo)

      //  Gets called when this module's state is getting restored, typically when a user opens a preset with
      //  this module in it. The stateInfo parameter will contain whatever custom data you stored in GetStateInformation().
   //-------------------------------------------------------------------------------
   @Override
   public void SetStateInformation(byte[] stateInfo)
   {
      //[user-SetStateInformation]   Add your own code here



      //[/user-SetStateInformation]
   }


   //-------------------------------------------------------------------------------
   //  public byte[] GetStateInformationForVariations()

      //  Gets called when a user saves a variation with this module in it.
      //  Voltage Modular will automatically save the states of knobs, sliders, etc.,
      //  but if you have any custom state information you need to save, return it from this function.
   //-------------------------------------------------------------------------------
   @Override
   public byte[] GetStateInformationForVariations()
   {
      //[user-GetStateInformationForVariations]   Add your own code here



      return GetStateInformation();
      //[/user-GetStateInformationForVariations]
   }


   //-------------------------------------------------------------------------------
   //  public void SetStateInformationForVariations(byte[] stateInfo)

      //  Gets called when a user loads a variation with this module in it.
      //  The stateInfo parameter will contain whatever custom data you stored in GetStateInformationForVariations().
   //-------------------------------------------------------------------------------
   @Override
   public void SetStateInformationForVariations(byte[] stateInfo)
   {
      //[user-SetStateInformationForVariations]   Add your own code here
      SetStateInformation(stateInfo);



      //[/user-SetStateInformationForVariations]
   }


   // Auto-generated variables
   private VoltageKnob pulseWidth;
   private VoltageToggle noiseButton;
   private VoltageToggle squareButton;
   private VoltageToggle sawButton;
   private VoltageToggle triangleButton;
   private VoltageMidiJack midiOut;
   private VoltageSlider release;
   private VoltageSlider sustain;
   private VoltageSlider decay;
   private VoltageSlider attack;


   //[user-code-and-variables]    Add your own variables and functions here
   
   private void sendShortPulseWidth() {
      try {
         ShortMessage m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, SidConstants.CC_PW_SINGLE_BYTE, (int)pulseWidth.GetValue());
         midiOut.AddMessage(m);
      } catch (Exception e) {}
   }
   
   private void sendPulseWidth()
   {
      ShortMessage m = new ShortMessage();
      
      int value = (int)Math.round(pulseWidth.GetValue());

      // extract the low byte
      int lowByte = value & 0xFF;

      // extract the high byte
      int highByte = (value >> 8) & 0xFF;
      
      try {
         m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, SidConstants.CC_PW_LO_BYTE, lowByte);
         midiOut.AddMessage(m);

         m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, SidConstants.CC_PW_HI_BYTE, highByte);
         midiOut.AddMessage(m);
      } catch (Exception e) {}
   }

   private void sendADSR()
   {
      try {      
         ShortMessage m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, SidConstants.CC_AMP_ATTACK, (int)attack.GetValue());
         midiOut.AddMessage(m);

         m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, SidConstants.CC_AMP_DECAY, (int)decay.GetValue());
         midiOut.AddMessage(m);

         m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, SidConstants.CC_AMP_SUSTAIN, (int)sustain.GetValue());
         midiOut.AddMessage(m);

         m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, SidConstants.CC_AMP_RELEASE, (int)release.GetValue());
         midiOut.AddMessage(m);
      } catch(Exception e) {}    
   }

   private void sendShapes()
   {
      try {      
         ShortMessage m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, SidConstants.CC_TRIANGLE, (int)triangleButton.GetValue());
         midiOut.AddMessage(m);

         m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, SidConstants.CC_SAW, (int)sawButton.GetValue());
         midiOut.AddMessage(m);

         m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, SidConstants.CC_PULSE, (int)squareButton.GetValue());
         midiOut.AddMessage(m);

         m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, SidConstants.CC_NOISE, (int)noiseButton.GetValue());
         midiOut.AddMessage(m);
      } catch(Exception e) {}            
   }


   private void sendMidi()
   {
      sendShapes();
      sendADSR();
      sendShortPulseWidth();
   }
   //[/user-code-and-variables]
}

 